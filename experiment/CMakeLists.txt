cmake_minimum_required(VERSION 3.7...3.27)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(PQCBench LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "binaries")
set(CMAKE_CXX_STANDARD 20)

include_directories("source/kyber/include")
include_directories("source/kyber/sha3/include")
include_directories("source/kyber/subtle/include")

find_library(CRYPTOPP cryptopp)

add_executable(payload source/payload.cpp)
add_executable(benchmark source/benchmark.cpp)
add_executable(eccKEM source/eccKEM.cpp)
add_executable(kyberKEM source/kyberKEM.cpp)

target_link_libraries(eccKEM PRIVATE "${CRYPTOPP}")


