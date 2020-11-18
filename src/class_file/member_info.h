//
// Created by tairy on 2020/11/15.
//

#ifndef TJVMSRC_MEMBER_INFO_H
#define TJVMSRC_MEMBER_INFO_H

#include "stdlib.h"
#include "attribute_info.h"
#include "class_reader.h"

struct member_info {
    u_int16_t access_flags;             // 访问控制符

    u_int16_t name_index;               // 成员名在常量池中的索引

    u_int16_t description_index;        // 描述符字段

    struct attribute_infos *attributes;  // 属性表
};

struct member_infos {

    u_int16_t size;

    struct member_info **infos;

};

static struct member_infos *read_members(struct class_reader *r, struct cp *p) {
    u_int16_t member_count = read_uint16(r);
    struct member_infos *rs = malloc(sizeof(struct member_infos));
    struct member_info **infos = malloc(sizeof(struct member_info *) * member_count);
    rs->size = member_count;

    for (int i = 0; i < member_count; i++) {
        infos[i] = malloc(sizeof(struct member_info));
        infos[i]->access_flags = read_uint16(r);
        infos[i]->name_index = read_uint16(r);
        infos[i]->description_index = read_uint16(r);
        infos[i]->attributes = read_attributes(r, p);
    }

    rs->infos = infos;
    return rs;
}

#endif //TJVMSRC_MEMBER_INFO_H
