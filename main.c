#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>
#include "unp_prac.h"
#include "struct.h"
#include "callback/close_callback.h"

#define DEFAULT_PORT 7000
#define DEFAULT_BACKLOG 128

uv_loop_t *loop;
struct sockaddr_in addr;
const char * ENTER="请输入任意文字：\n";

typedef struct {
    //uv_write_t放在第一位->内存布局中这个struct和uv_write_t起点相同->write_req_t和uv_write_t的指针可以互相强转
    // 注意，单向安全，反响不安全，你懂得吧。。
    // 互相强转下面有体现
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_malloc_write_req(uv_write_t *req) {
    write_req_t *wr = (write_req_t*) req;
    // 释放malloc出来的buf（容器）
    free(wr->buf.base);
    // 释放write本身[直接声明的write不需要释放]
    //free(wr);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void on_echo_write(uv_write_t *req, int status) {
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free_malloc_write_req(req);
}

void on_first_write(uv_write_t *req, int status){
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }else{
        fprintf(stderr,"提示发送成功\n");
    }
}



void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {

    if (nread > 0) {
        //截取char*，增加\0【明显不合理】
        //buf->base[nread]=0;
        //fprintf(stderr,"%ld:%s",nread,buf->base);
        // 改为使用如下方法
        fprintf(stderr,"%ld:",nread);
        Writen(stderr->_fileno,buf->base,nread);

        //在站上
        write_req_t req;
        //在堆上（需要手动free）
        // write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
        req.buf = uv_buf_init(buf->base, nread);
        uv_write((uv_write_t*) &req, client, &req.buf, 1, on_echo_write);
        return;
    }
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) client, free_client);
    }
    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        //发送提示信息
        write_req_t req;
        req.buf = uv_buf_init((char *)ENTER, strlen(ENTER));
        uv_write((uv_write_t*) &req,(uv_stream_t*)  client, &req.buf, 1, on_first_write);
        client->data=calloc(1, sizeof(Context));
        uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    }
    else {
        uv_close((uv_handle_t*) client, NULL);
    }
}

int main() {
    loop = uv_default_loop();

    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr);
    printf("excute: nc localhost 7000\n");
    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}