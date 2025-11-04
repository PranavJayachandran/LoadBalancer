cmake_minimum_required(VERSION 3.16)
project(LoadBalancer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SERVER_FILES src/*/server.cpp)
add_executable(LoadBalancer src/main.cpp ${SERVER_FILES})
target_include_directories(LoadBalancer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


