cmake_minimum_required(VERSION 3.9)
project(tjvmTest)

set(CMAKE_CXX_STANDARD 11)

get_filename_component(PARENT_DIR ../.. ABSOLUTE)
include_directories("${PARENT_DIR}/src/")

add_executable(class_file_test
        ${PARENT_DIR}/src/class_file/constant_pool.h
        ${PARENT_DIR}/src/class_file/member_info.h
        ${PARENT_DIR}/src/class_file/attribute_info.h
        ${PARENT_DIR}/src/class_file/class_reader.h
        ${PARENT_DIR}/src/class_file/class_file.c
        ${PARENT_DIR}/src/class_file/class_file.h
        ${PARENT_DIR}/src/class_path/class_path.c
        ${PARENT_DIR}/src/class_path/class_path.h
        ${PARENT_DIR}/src/util/log.c
        ${PARENT_DIR}/src/util/log.h
        ${PARENT_DIR}/src/util/file.c
        ${PARENT_DIR}/src/util/file.h
        class_file_test.c)

target_link_libraries(class_file_test -lzip)