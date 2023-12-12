#ifndef LS_H
#define LS_H

#include <stdlib.h>         // for malloc(), free()
#include <sys/stat.h>       // for stat(), lstat()
#include <sys/time.h>       // time_t tv_sec 
#include <stdio.h>          // for printf()

#define  MAX_SIZE 100       // max array size
#define  MAX_FILE 255       // max len of file name

/* A structure to hold information about options */
typedef struct options
{
    int a;
    int t;
} ls_options;


/* A structure to hold information about the content's name and the content's timestamp for ls -t */
typedef struct dir_content
{
    char file_name[MAX_FILE];
    time_t timestamp;
} dir_c;


/* Checking for options -a, -t and returning 0 if false, 1 if true */
ls_options* check_op(int ac, char **av);

/* Printing sorted array */
void print_array(char **array, int size);

/* Getting a timestamp for each CL argument or directory content, if option -t */
long get_timestamp (char *path);

/* Sort array by lstat() time */
void sort_cl_input_by_time(char **array, int size);

/* Sorting files by time last modified to mimic ls -t command. If timestamps are equal, comparing file names in alphabetical order */
void sort_dir_content_by_time(dir_c *array, int array_len);

/* Sorting in an alphabetical order */
void sort_array_alph(char **array, int size);

/* Creates a full path by concatenating directory and file name, required for lstat() */
char* create_full_path(char* directory, char* dir_entry);

/* List contents of the directory if there is only one directory given as CL input */
void list_dir (char *path, int flag, int op_a, int op_t);

/* If input is multiple directories, list these in alphabetical order by default (unless: option -t), 
*  each printed as "dir:" and a newline before each directory, after the first directory 
*/
void list_mult_dir(char **array, int size, int flag, int op_a, int op_t);

/* Processing options/flags (-t, -a) based on the number of args/operands entered as CL input after the options/flags */
void send_op(int ls_time, int ls_hidden, int flag, char *path, char **array, int size);

/* Processing args/operands based on the number of args/operands entered as CL input (if there is more than 1 directory, dir displayed with ':') */
void send_args(int ls_time, int ls_hidden, int flag, char *path, char **array, int size);

#endif