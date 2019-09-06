cmake_minimum_required(VERSION 3.13)
project(libuv_test C)

set(CMAKE_C_STANDARD 11)


add_executable(libuv_test main.c)
target_link_libraries(libuv_test /usr/lib/libuv.so)

