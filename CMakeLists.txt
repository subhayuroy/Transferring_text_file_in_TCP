cmake_minimum_required(VERSION 3.15)
project(Transferring_text_file_in_TCP C)

set(CMAKE_C_STANDARD 99)

add_executable(Transferring_text_file_in_TCP server.c)
#add_executable(Transferring_text_file_in_TCP client.c)