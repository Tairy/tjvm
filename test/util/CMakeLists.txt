cmake_minimum_required(VERSION 3.9)
project(tjvmTest)

set(CMAKE_CXX_STANDARD 11)

get_filename_component(PARENT_DIR ../.. ABSOLUTE)
include_directories("${PARENT_DIR}/src/")

add_executable(hash_map_test
        ${PARENT_DIR}/src/util/hash_map.h
        ${PARENT_DIR}/src/util/util.h
        hash_map_test.c
        )

target_link_libraries(hash_map_test -lzip)