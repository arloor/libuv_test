//
// Created by arloor on 2020/3/26.
//

#ifndef LIBUV_TEST_STRUCT_H
#define LIBUV_TEST_STRUCT_H
typedef enum {
    init,end
}SOCKS5_STATUS;

// 保存socks5握手状态
typedef struct {
    SOCKS5_STATUS status;
}Context;

#endif //LIBUV_TEST_STRUCT_H
