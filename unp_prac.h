//
// Created by arloor on 2020/3/25.
//

#ifndef LIBUV_TEST_UNP_PRAC_H
#define LIBUV_TEST_UNP_PRAC_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define port 4657 //请每次运行之后都更改这个端口号，因为TCP会禁止不久前使用过的IP投入新的使用

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

typedef struct sockaddr SA;


/**
 * 自定义io相关
 * 原生的不带缓冲IO（read\write）在套接字描述符上的IO可能存在输入或者输出的字节数少于请求的数量
 * 原因是内核中用于套接字的缓冲区可能已经到达极限。
 * 下面这些函数就是用于解决这个问题。
 */
ssize_t Readline(int, void *, size_t);

ssize_t Readn(int, void *, size_t);

void Writen(int, void *, size_t);

/**
 * 错误处理相关
 */
void err_dump(const char *, ...);

void err_msg(const char *, ...);

void err_quit(const char *, ...);

void err_ret(const char *, ...);

void err_sys(const char *, ...);

#endif //LIBUV_TEST_UNP_PRAC_H
