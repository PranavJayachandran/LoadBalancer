cmake_minimum_required(VERSION 3.16)
project(LoadBalancer VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_INSTALL OFF)
# set(ABSL_ENABLE_INSTALL ON)
# set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/.cmake-cache")

# FetchContent_Declare(
#   abseil
#   GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
#   GIT_TAG        20250814.1
# )
# FetchContent_MakeAvailable(abseil)
#
# FetchContent_Declare(
#   gRPC
#   GIT_REPOSITORY https://github.com/grpc/grpc
#   GIT_TAG        v1.76.0
# )
# set(FETCHCONTENT_QUIET OFF)
# FetchContent_MakeAvailable(gRPC)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
file(GLOB_RECURSE SERVER_FILES src/*.cpp)
set(GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(LoadBalancer src/main.cpp ${SERVER_FILES}
  ${GENERATED_DIR}/loadbalancer.pb.cc
  ${GENERATED_DIR}/loadbalancer.grpc.pb.cc)
target_link_libraries(LoadBalancer PRIVATE gRPC::grpc++ protobuf::libprotobuf gRPC::grpc++_reflection)
target_include_directories(LoadBalancer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include,
  ${GENERATED_DIR})

