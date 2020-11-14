//
// Created by tairy on 2020/11/14.
//

#include <stdarg.h>
#include <stdio.h>
#include "log.h"

void log_debug(char *format, ...) {
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf(">> %s\n", buf);
    va_end(list);
}

void log_info(char *format, ...) {
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf(">> %s\n", buf);
    va_end(list);
}

void log_warn(char *format, ...) {
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s%s%s\n", COLOR_YEL, buf, COLOR_WHT);
    va_end(list);
}

void log_error(char *file, int line, char *format, ...) {
    char buf[256] = {0};
    va_list list;
    va_start(list, format);
    vsprintf(buf, format, list);
    printf("%s%s:%d >> %s%s\n", COLOR_RED, file, line, buf, COLOR_WHT);
    va_end(list);
}
