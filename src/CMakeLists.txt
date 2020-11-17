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
        runtime/class_loader.c
        runtime/class_loader.h
        util/log.c
        util/log.h
        util/file.c
        util/file.h
        util/util.h
        tjvm.c)

target_link_libraries(tjvm -lzip)