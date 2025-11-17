cmake_minimum_required(VERSION 3.16)
project(LoadBalancer VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_INSTALL OFF)
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

# unit test 
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SOURCES tests/*.cpp)

add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests
    gtest
    gtest_main
    pthread
    # Link your main library if you have one
)

add_test(NAME run_unit_tests COMMAND run_tests)
