#include "logger.h"

#include <time.h>

FILE* log_init(char* filename) {
    FILE* log_file = fopen(filename, "w");
    if (log_file == NULL) {
        return NULL;
    }
    return log_file;
}

int logcat(FILE* log_file, char* message, log_level level) {
    char* level_str;
    switch (level) {
        case debug:
            level_str = "DEBUG";
            break;
        case info:
            level_str = "INFO";
            break;
        case warning:
            level_str = "WARNING";
            break;
        case error:
            level_str = "ERROR";
            break;
        default:
            break;
    }

    time_t current_time;
    struct tm* time_info;
    char timeString[9];

    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    fprintf(log_file, "[%s] %s - %s\n", level_str, timeString, message);

    return 0;
}

int log_close(FILE* log_file) {
    if (log_file != NULL) {
        fclose(log_file);
    }
    return 0;
}
