/*
 * a.c
 * empty msg loop
 * 这个例子新建了一个消息队列，但队列里没有任何消息，程序直接退出
 * Created on 2016/9/10
 */
#include <stdio.h>
#include <stdlib.h>
#include "uv.h"

int main(int argc, char *argv[])
{
    uv_loop_t *loop = uv_loop_new();  // 可以理解为新建一个消息队列
    uv_run(loop, UV_RUN_DEFAULT);     // 启动消息队列，UV_RUN_DEFAULT模式下，当消息数为0时，就会退出消息循环。
    printf("hello, world\n");
    return 0;
}
