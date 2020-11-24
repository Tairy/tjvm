cmake_minimum_required(VERSION 3.9)
project(tjvmSrc)

set(CMAKE_CXX_STANDARD 11)

include_directories(".")

add_executable(tjvm
        class_path/class_path.c
        class_path/class_path.h
        class_file/constant_pool.h
        class_file/member_info.h
        class_file/attribute_info.h
        class_file/class_reader.h
        class_file/class_file.c
        class_file/class_file.h
        runtime/access_flags.h
        runtime/object.c
        runtime/object.h
        runtime/thread.c
        runtime/thread.h
        runtime/stack.c
        runtime/stack.h
        runtime/frame.c
        runtime/frame.h
        runtime/local_vars.c
        runtime/local_vars.h
        runtime/operand_stack.c
        runtime/operand_stack.h
        runtime/class.c
        runtime/class.h
        runtime/field.c
        runtime/field.h
        runtime/method.c
        runtime/method.h
        runtime/class_loader.c
        runtime/class_loader.h
        runtime/slot.c
        runtime/slot.h
        runtime/oop.c
        runtime/oop.h
        runtime/runtime_constant_pool.c
        runtime/runtime_constant_pool.h
        util/log.c
        util/log.h
        util/file.c
        util/file.h
        util/hash_map.h
        util/util.h
        util/number.h
        interpreter/bytecode_reader.h
        interpreter/bytecode_interpreter.h
        interpreter/bytecode_interpreter.c
        interpreter/ins_constant.h
        interpreter/ins_compare.h
        interpreter/ins_load.h
        interpreter/ins_opcode.h
        interpreter/ins_store.h
        interpreter/ins_stack.h
        interpreter/ins_math.h
        interpreter/ins_convert.h
        interpreter/ins_control.h
        interpreter/ins_reference.h
        interpreter/ins_extend.h
        interpreter/ins_reserved.h
        tjvm.c)

target_link_libraries(tjvm -lzip)