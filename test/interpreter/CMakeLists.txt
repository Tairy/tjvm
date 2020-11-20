cmake_minimum_required(VERSION 3.9)
project(tjvmTest)

set(CMAKE_CXX_STANDARD 11)

get_filename_component(PARENT_DIR ../.. ABSOLUTE)
include_directories("${PARENT_DIR}/src/")

add_executable(class_path_test
        ${PARENT_DIR}/src/class_path/class_path.c
        ${PARENT_DIR}/src/class_path/class_path.h
        ${PARENT_DIR}/src/class_file/constant_pool.h
        ${PARENT_DIR}/src/class_file/member_info.h
        ${PARENT_DIR}/src/class_file/attribute_info.h
        ${PARENT_DIR}/src/class_file/class_reader.h
        ${PARENT_DIR}/src/class_file/class_file.c
        ${PARENT_DIR}/src/class_file/class_file.h
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
        ${PARENT_DIR}/src/runtime/oop.c
        ${PARENT_DIR}/src/runtime/oop.h
        ${PARENT_DIR}/src/runtime/runtime_constant_pool.c
        ${PARENT_DIR}/src/runtime/runtime_constant_pool.h
        ${PARENT_DIR}/src/util/log.c
        ${PARENT_DIR}/src/util/log.h
        ${PARENT_DIR}/src/util/file.c
        ${PARENT_DIR}/src/util/file.h
        ${PARENT_DIR}/src/util/util.h
        ${PARENT_DIR}/src/util/number.h
        ${PARENT_DIR}/src/interpreter/bytecode_reader.h
        ${PARENT_DIR}/src/interpreter/bytecode_interpreter.h
        ${PARENT_DIR}/src/interpreter/bytecode_interpreter.c
        ${PARENT_DIR}/src/interpreter/ins_constant.h
        ${PARENT_DIR}/src/interpreter/ins_compare.h
        ${PARENT_DIR}/src/interpreter/ins_load.h
        ${PARENT_DIR}/src/interpreter/ins_opcode.h
        ${PARENT_DIR}/src/interpreter/ins_store.h
        ${PARENT_DIR}/src/interpreter/ins_stack.h
        ${PARENT_DIR}/src/interpreter/ins_math.h
        ${PARENT_DIR}/src/interpreter/ins_convert.h
        ${PARENT_DIR}/src/interpreter/ins_control.h
        ${PARENT_DIR}/src/interpreter/ins_reference.h
        ${PARENT_DIR}/src/interpreter/ins_extend.h
        ${PARENT_DIR}/src/interpreter/ins_reserved.h
        interpreter.c)

target_link_libraries(class_path_test -lzip)