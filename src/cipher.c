#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

int menu();
void strZeroInput(char *str);
void printFile(FILE *f);

int main() {
    while (1) {
        char fileName[50];
        int m = menu();
        FILE *f;
#ifdef Quest_5
        FILE *log = log_init("log.txt");
#endif
        switch (m) {
            case 1:
                fgets(fileName, 50, stdin);
                strZeroInput(fileName);
                f = fopen(fileName, "r");
                if (f == NULL) {
#ifdef Quest_5
                    logcat(log, "Ошибка при открытии файла ", error);
#endif
                    printf("n/a\n");
                } else {
                    fseek(f, 0, SEEK_END);
                    long pos = ftell(f);
                    if (pos == 0) {
                        printf("n/a\n");
                        fclose(f);
                    } else {
                        rewind(f);
                        printFile(f);
                        fclose(f);
                    }
                }
                continue;
            case 2:
                char buf2[1000];
                fgets(buf2, 1000, stdin);
                f = fopen(fileName, "r");
                if (f == NULL) {
                    printf("n/a\n");
                } else {
                    f = fopen(fileName, "a");
                    fputs(buf2, f);
                    fclose(f);
                    f = fopen(fileName, "r");
                    printFile(f);
                    fclose(f);
                }
                continue;
            case 3:
                char directory[] = "../src/ai_modules/";
                DIR *dp = opendir(directory);
                if (!dp) {
                    printf("n/a\n");
                    continue;
                }
                int step = 0;
                char buffer[20];
                fgets(buffer, 20, stdin);
                if (atoi(buffer) == 0) {
                    printf("n/a\n");
                    continue;
                }
                step = atoi(buffer);
                struct dirent *de;
                FILE *f2;
                char i = '1';
                char newName[10] = "file";
                while ((de = readdir(dp)) != NULL) {
                    char *path = malloc(strlen(directory) * strlen(de->d_name) * sizeof(char));
                    sprintf(path, "%s%s", directory, de->d_name);
                    if (de->d_name[strlen(de->d_name) - 1] == 'h' &&
                        de->d_name[strlen(de->d_name) - 2] == '.') {
                        f = fopen(path, "w");
                        fputs("\0", f);
                        fclose(f);
                        free(path);
                    } else if (de->d_name[strlen(de->d_name) - 1] == 'c' &&
                               de->d_name[strlen(de->d_name) - 2] == '.') {
                        f = fopen(path, "r");
                        f2 = fopen(newName, "w");
                        char c;
                        int flag;
                        while (!feof(f)) {
                            c = getc(f);
                            flag = 0;
                            if (c >= 'A' && c <= 'Z') {
                                c = c + (step % 26);
                                if (c > 'Z') c = 'A' + (c - 'Z') - 1;
                                fputc(c, f2);
                                flag = 1;
                            }
                            if (c >= 'a' && c <= 'z') {
                                c = c + (step % 26);
                                if (c > 'z') c = 'a' + (c - 'z') - 1;
                                fputc(c, f2);
                                flag = 1;
                            }
                            if (!flag) {
                                fputc(c, f2);
                            }
                        }
                        fclose(f);
                        fclose(f2);
                        f = fopen(path, "w");
                        f2 = fopen(newName, "r");
                        while (!feof(f2)) {
                            c = getc(f2);
                            fputc(c, f);
                        }
                        fclose(f);
                        fclose(f2);
                        remove(newName);
                        free(path);
                        i = (char)(i + 1);
                        newName[4] = i;
                        newName[5] = '\0';
                    } else {
                        continue;
                    }
                }
                closedir(dp);
                continue;
            case 0:
                printf("n/a\n");
                continue;
            case 4:
                break;
        }
#ifdef Quest_5
        log_close(log);
#endif
    }
    return 0;
}

void printFile(FILE *f) {
    while (!feof(f)) {
        char buf3[1000];
        if (fgets(buf3, 1000, f) != NULL) {
            printf("%s", buf3);
        }
    }
}

void strZeroInput(char *str) {
    for (int i = 0;; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

int menu() {
    char input[10];
    while (1) {
        fgets(input, 10, stdin);
        if (!strcmp(input, "1\n")) {
            return 1;
        } else if (!strcmp(input, "-1\n")) {
            return 4;
        } else if (!strcmp(input, "2\n")) {
            return 2;
        } else if (!strcmp(input, "3\n")) {
            return 3;
        } else {
            return 0;
        }
    }
}
