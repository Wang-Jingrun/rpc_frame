cmake_minimum_required(VERSION 3.22)
project(simple_rpc_frame)

set(CMAKE_CXX_STANDARD 14)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 包含头文件所在目录
include_directories("./")

file(GLOB_RECURSE SOURCES "utility/*.cpp" "socket/*.cpp" "thread/*.cpp"
         "frame/*.cpp" "task/*.cpp" "serialize/*.cpp" "rpc/*.cpp")


add_executable(main ${SOURCES} main.cpp)
add_executable(server ${SOURCES} server.cpp)
add_executable(client ${SOURCES} client.cpp)
