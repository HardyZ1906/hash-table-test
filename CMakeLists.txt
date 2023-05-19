cmake_minimum_required(VERSION 3.16)
project(hybrid)

set(CMAKE_CXX_STANDARD 11)
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0 -fsanitize=address -fno-omit-frame-pointer")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -O3")
endif()

include_directories(include)

add_executable(hybrid src/MurmurHash2.cpp src/util.cpp test/hash_table_test.cpp)

target_link_libraries(hybrid pmem pmemobj)