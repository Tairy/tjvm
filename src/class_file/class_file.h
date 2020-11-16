//
// Created by tairy on 2020/11/15.
//

#ifndef TJVMSRC_CLASS_FILE_H
#define TJVMSRC_CLASS_FILE_H

#include "stdlib.h"
#include "constant_pool.h"
#include "member_info.h"
#include "attribute_info.h"
#include "class_reader.h"

struct class_file {
    u_int32_t magic;                // 魔数：0xCAFEBABE

    u_int16_t minor_version;        // 类文件次版本号

    u_int16_t major_version;        // 类文件主版本号

    struct cp *constant_pool;       // 该文件的常量池，有些会成为运行时常量的一部分

    u_int16_t access_flags;         // 类访问控制，有是否 public、final、abstract

    u_int16_t this_class;           // 本类在常量池中的索引

    u_int16_t super_class;          // 父类在常量池中的索引

    u_int16_t interfaces_count;     // 实现的接口数量

    u_int16_t *interfaces;          // 接口索引

//    u_int16_t fields_count;         // 类中字段的数量

    struct member_infos *fields;     // 字段表

    struct member_infos *methods;   // 方法表

    struct attribute_infos *attribute_infos;  // 属性表

    struct class_file *(*read_as_class_file)(struct class_reader *r);
};

struct class_file *read_as_class_file(struct class_reader *r);

#endif //TJVMSRC_CLASS_FILE_H
