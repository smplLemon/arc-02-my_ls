#include "utils.h"
#include <stdbool.h>        // for check_input()
#include <sys/stat.h>       // for stat(), lstat()
#include <stdlib.h>         // for malloc(), free()


/* Checking if input entered in the command line exists */
bool check_input(int ac, char *path_name)
{
    struct stat input;
    bool correct = false;
    for (int i = 1; i < ac; i++)
    {
        if (stat(path_name, &input) == 0)
        {
            correct = true;
            return 1; 
        }
    }
    if(!correct)
    {
        printf("my_ls: cannot access '%s': No such file or directory\n", path_name);
    }
    return 0;
}


/* Implementation of strlen() from string.h */
int my_strlen(char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        i++;
    }
    return i;
}


/* Implementation of strcpy() from string.h */
char* my_strcpy(char *destination, char* source)
{
    int i = 0;
    while(source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    return destination;
}


/* Implementation of strcmp() from string.h */
int my_strcmp(char *string1, char* string2)
{
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0' && string1[i] == string2[i])
    {
        i++;
    }

    if (string1[i] == string2[i])
    {
        return 0;
    }
    else if (string1[i] > string2[i])
    {
        return 1;
    }
    else
    {
        return -1;
    }
}


/* Implementation of strcat() from string.h */
char* my_strcat(char *destination, char* source)
{
    int i = 0;
    int j = 0;
    while (destination[j] != '\0')
    {
        j++;
    }
    while(source[i] != '\0')
    {
        destination[j] = source[i];
        i++;
        j++;
    }
    destination[j] = '\0';
    return destination;
}


/* Free memory allocated for array strings */
void free_strings(char **array, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(array[i]);
    }
}