
cmake_minimum_required(VERSION 3.10.0)

project(EasyServer VERSION 0.1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置通用源文件
set(SOURCES
    "server/server.cpp"
)

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 添加可执行文件, 使用配置好的 "SOURCES" 变量
add_executable(${TARGET} ${SOURCES})