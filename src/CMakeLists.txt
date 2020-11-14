cmake_minimum_required(VERSION 3.9)
project(tjvmSrc)

set(CMAKE_CXX_STANDARD 11)

add_executable(tjvm
        classpath/classpath.c
        classpath/classpath.h
        util/log.c
        util/log.h
        util/file.c
        util/file.h
        util/util.h
        tjvm.c)

target_link_libraries(tjvm -lzip)