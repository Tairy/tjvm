//
// Created by tairy on 2020/11/15.
//

#include "class_file.h"
#include "constant_pool.h"
#include "util/log.h"
#include "util/util.h"

void check_magic(u_int32_t magic);

void check_class_version(u_int16_t major_version, u_int16_t minor_version);

struct cp_info *read_constant_info(struct class_reader *r, struct cp *cp);

struct cp *read_constant_pool(struct class_reader *r);

struct class_file *read_as_class_file(struct class_reader *r) {
    struct class_file *rs = (struct class_file *) malloc(sizeof(struct class_file));
    rs->magic = read_uint32(r);
    check_magic(rs->magic);
    rs->minor_version = read_uint16(r);
    rs->major_version = read_uint16(r);
    check_class_version(rs->minor_version, rs->major_version);

    struct cp *csp = read_constant_pool(r);

    rs->constant_pool = csp;
    rs->access_flags = read_uint16(r);
    rs->this_class = read_uint16(r);
    rs->super_class = read_uint16(r);
    rs->interfaces = read_uint16_s(r, &(rs->interfaces_count));
    rs->fields = read_members(r, csp);
    rs->methods = read_members(r, csp);
    rs->attribute_infos = read_attributes(r, csp);
    return rs;
}

void check_magic(u_int32_t magic) {
}

void check_class_version(u_int16_t major_version, u_int16_t minor_version) {
//    switch (major_version) {
//        case 45:
//            return;
//        case 46:
//        case 47:
//        case 48:
//        case 49:
//        case 50:
//        case 51:
//        case 52:
//            if (minor_version == 0) {
//                return;
//            }
//        default:
//            log_error(__FILE__, __LINE__, "java.lang.UnsupportedClassVersionError!");
//    }
}

struct cp_info *read_constant_info(struct class_reader *r, struct cp *cp) {

}

struct cp *read_constant_pool(struct class_reader *r) {
    struct cp *cp = (struct cp *) malloc(sizeof(struct cp));
    cp->len = read_uint16(r);

    struct cp_info **infos = malloc(sizeof(struct cp_info) * (cp->len - 1));
    for (int i = 1, len = cp->len; i < len; i++) {
        infos[i] = malloc(sizeof(struct cp_info));
        infos[i]->tag = read_uint8(r);
        infos[i]->v1 = read_uint16(r);

        if (infos[i]->tag == CONSTANT_Double_info || infos[i]->tag == CONSTANT_Long_info) {
            infos[i]->v2 = read_uint16(r);
            i++;
        }
    }
}