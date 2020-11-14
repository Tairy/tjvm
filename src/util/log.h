//
// Created by tairy on 2020/11/14.
//

/**
 * 日志操作
 */

#ifndef TJVM_LOG_H
#define TJVM_LOG_H

#define COLOR_NRM   "\x1B[0m"
#define COLOR_RED   "\x1B[31m"
#define COLOR_GRN   "\x1B[32m"
#define COLOR_YEL   "\x1B[33m"
#define COLOR_BLU   "\x1B[34m"
#define COLOR_MAG   "\x1B[35m"
#define COLOR_CYN   "\x1B[36m"
#define COLOR_WHT   "\x1B[37m"

void log_debug(char *format, ...);

void log_info(char *format, ...);

void log_warn(char *format, ...);

void log_error(char *file, int line, char *format, ...);

#endif //TJVM_LOG_H
