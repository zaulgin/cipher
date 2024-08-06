#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>

typedef enum log_level { debug, trace, info, warning, error } log_level;

FILE* log_init(char* filename);

int logcat(FILE* log_file, char* message, log_level level);

int log_close(FILE* log_file);
#endif
