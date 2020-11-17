cmake_minimum_required(VERSION 3.9)
project(tjvmTest)

set(CMAKE_CXX_STANDARD 11)

get_filename_component(PARENT_DIR ../.. ABSOLUTE)
include_directories("${PARENT_DIR}/src/")

add_executable(runtime_test
        ${PARENT_DIR}/src/class_path/class_path.c
        ${PARENT_DIR}/src/class_path/class_path.h
        ${PARENT_DIR}/src/class_file/constant_pool.h
        ${PARENT_DIR}/src/class_file/member_info.h
        ${PARENT_DIR}/src/class_file/attribute_info.h
        ${PARENT_DIR}/src/class_file/class_reader.h
        ${PARENT_DIR}/src/class_file/class_file.c
        ${PARENT_DIR}/src/class_file/class_file.h
        ${PARENT_DIR}/src/util/log.c
        ${PARENT_DIR}/src/util/log.h
        ${PARENT_DIR}/src/util/file.c
        ${PARENT_DIR}/src/util/file.h
        ${PARENT_DIR}/src/util/util.h
        ${PARENT_DIR}/src/util/number.h
        ${PARENT_DIR}/src/runtime/object.c
        ${PARENT_DIR}/src/runtime/object.h
        ${PARENT_DIR}/src/runtime/thread.c
        ${PARENT_DIR}/src/runtime/thread.h
        ${PARENT_DIR}/src/runtime/stack.c
        ${PARENT_DIR}/src/runtime/stack.h
        ${PARENT_DIR}/src/runtime/frame.c
        ${PARENT_DIR}/src/runtime/frame.h
        ${PARENT_DIR}/src/runtime/local_vars.c
        ${PARENT_DIR}/src/runtime/local_vars.h
        ${PARENT_DIR}/src/runtime/operand_stack.c
        ${PARENT_DIR}/src/runtime/operand_stack.h
        ${PARENT_DIR}/src/runtime/class.c
        ${PARENT_DIR}/src/runtime/class.h
        ${PARENT_DIR}/src/runtime/class_loader.c
        ${PARENT_DIR}/src/runtime/class_loader.h
        ${PARENT_DIR}/src/runtime/slot.c
        ${PARENT_DIR}/src/runtime/slot.h
        runtime_data_area_test.c
        )

target_link_libraries(runtime_test -lzip)