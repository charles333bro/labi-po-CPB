cmake_minimum_required(VERSION 3.10)
project(lab7)
set(CMAKE_CXX_STANDARD 17)


link_libraries(ws2_32)

add_executable(udp_server udp_server.cpp)
add_executable(udp_client udp_client.cpp)
add_executable(tcp_server tcp_server.cpp)
add_executable(tcp_client tcp_client.cpp)