
cmake_minimum_required(VERSION 3.10.0)

project(EasyServer VERSION 0.1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含当前项目的顶层目录
include_directories(./)

# 启用调试模式（禁用优化，保留调试信息）
set(CMAKE_BUILD_TYPE Debug)  # 或在命令行指定 -DCMAKE_BUILD_TYPE=Debug

# 强制生成调试信息（适用于所有构建类型，可选）
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")  # C++

# 设置通用源文件
set(SOURCES
    "socketClass/socket.cpp"
    "server/server.cpp"

)

set(SOURCES2
    "socketClass/socket.cpp"
    "client/client.cpp"
)

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 添加可执行文件, 使用配置好的 "SOURCES" 变量
add_executable(${TARGET} ${SOURCES})
add_executable(clientOne ${SOURCES2})
