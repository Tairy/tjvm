//
// Created by tairy on 2020/11/25.
//

#include "method_descriptor_parser.h"
#include "util/log.h"
#include "string.h"
#include "stdio.h"

void check_param_start(struct method_descriptor_parser *parser);

void parse_param_types(struct method_descriptor_parser *parser);

void check_param_end(struct method_descriptor_parser *parser);

void parse_return_type(struct method_descriptor_parser *parser);

char *parse_object_type(struct method_descriptor_parser *parser);

char *parse_array_type(struct method_descriptor_parser *parser);


struct method_descriptor *parse_method_descriptor(char *descriptor) {
    struct method_descriptor_parser *parser = malloc(sizeof(struct method_descriptor_parser));
    parser->raw = descriptor;
    parser->parsed = new_method_descriptor();
    parser->offset = 0;

    check_param_start(parser);
    parse_param_types(parser);
    check_param_end(parser);
    parse_return_type(parser);

    return parser->parsed;
}

void check_param_start(struct method_descriptor_parser *parser) {
    if (parser->raw[parser->offset++] != '(') {
        log_error(__FILE__, __LINE__, "method descriptor check start error: %s\n", parser->raw);
    }
}

void parse_param_types(struct method_descriptor_parser *parser) {
    switch (parser->raw[parser->offset++]) {
        case 'B':
            add_param_type(parser->parsed, "B\0");
            break;
        case 'C':
            add_param_type(parser->parsed, "C\0");
            break;
        case 'D':
            add_param_type(parser->parsed, "D\0");
            break;
        case 'F':
            add_param_type(parser->parsed, "F\0");
            break;
        case 'I':
            add_param_type(parser->parsed, "I\0");
            break;
        case 'J':
            add_param_type(parser->parsed, "J\0");
            break;
        case 'S':
            add_param_type(parser->parsed, "S\0");
            break;
        case 'Z':
            add_param_type(parser->parsed, "Z\0");
            break;
        case 'L':
            add_param_type(parser->parsed, parse_object_type(parser));
            break;
        case '[':
            add_param_type(parser->parsed, parse_array_type(parser));
            break;
        default:
            parser->offset--;
    }
}

void check_param_end(struct method_descriptor_parser *parser) {
    if (parser->raw[parser->offset++] != ')') {
        log_error(__FILE__, __LINE__, "method descriptor check end error: %s\n", parser->raw);
    }
}

void parse_return_type(struct method_descriptor_parser *parser) {
    if (parser->raw[parser->offset++] == 'V') {
        parser->parsed->return_type = (char *) 'V';
    }

    // todo 解析其他情况
}

char *parse_object_type(struct method_descriptor_parser *parser) {
    parser->offset--;
    u_int16_t len = strlen(parser->raw) - parser->offset + 1;
    char *str = malloc(len);
    memset(str, 0, len);
    while (parser->raw[parser->offset] != ';') {
        sprintf(str, "%s%c", str, parser->raw[parser->offset++]);
    }
    str[parser->offset] = '\0';
    return str;
}

char *parse_array_type(struct method_descriptor_parser *parser) {
    parser->offset--;
    u_int16_t len = strlen(parser->raw) - parser->offset + 1;
    char *str = malloc(len);
    memset(str, 0, len);
    while (parser->raw[parser->offset] != ';') {
        sprintf(str, "%s%c", str, parser->raw[parser->offset++]);
    }
    str[parser->offset] = '\0';
    return str;
}