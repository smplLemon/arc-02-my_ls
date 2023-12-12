#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>          // for printf()
#include <dirent.h>         // for DIR *dir
#include <stdbool.h>        // for check_input()

#define  MAX_FILE 255       // max len of file name

/* Checking if input entered in the command line exists */
bool check_input(int ac, char *path_name);

/* Implementation of strlen() from string.h */
int my_strlen(char *string);

/* Implementation of strcpy() from string.h */
char* my_strcpy(char *destination, char *source);

/* Implementation of strcmp() from string.h */
int my_strcmp(char *string1, char *string2);

/* Implementation of strcat() from string.h */
char* my_strcat(char *destination, char *source);

/* Free memory allocated for array strings */
void free_strings(char **array, int len);

#endif