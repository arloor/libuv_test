cmake_minimum_required(VERSION 3.13)
project(libuv_test C)

set(CMAKE_C_STANDARD 11)


add_executable(libuv_test main.c io/io.c io/error.c unp_prac.h io/readline.c io/readn.c)
target_link_libraries(libuv_test /usr/lib64/libuv.so)

add_executable(example example.c  io/io.c io/error.c unp_prac.h io/readline.c io/readn.c struct.h callback/close_callback.h)
target_link_libraries(example /usr/lib64/libuv.so)

