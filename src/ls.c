#include "ls.h"
#include "utils.h"


/* Checking for options -a, -t and returning 0 if false, 1 if true */
ls_options* check_op(int ac, char **av)
{
    ls_options *option = malloc(sizeof(ls_options));
    option->a = 0;
    option->t = 0;
    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] == '-')
        {
            for (int j = 1; av[i][j] != '\0'; j++)
            {
                switch(av[i][j])
                {
                    case 'a':
                        option->a = 1;
                        break;
                    case 't':
                        option->t = 1;
                        break;    
                    default:
                        printf("Usage: ./my_ls [options] [file... | directory...]\n");
                        break;
                }
            }
        }
    }
    return option;
}


/* Printing sorted array */
void print_array(char **array, int size)
{
    for (int j = 0; j < size; j++)
    {
        printf("%s\n", array[j]);
    }
}


/* Getting a timestamp for each CL argument or directory content, if option -t */
long get_timestamp (char *path)
{
    struct stat buffer;
    int result = lstat(path, &buffer);
    if (result == -1)
    {
        printf("Error obtaining timestamp.\n");
    }
    //long timestamp =  (buffer.st_mtim.tv_sec*1e9) + buffer.st_mtim.tv_nsec; // for DoCode
    long timestamp = buffer.st_mtime*1000000000; //NOTE: the older C library versions use: entry_info.st_mtime | for VSCode

    return timestamp;
}


/* Sort array by lstat() time */
void sort_cl_input_by_time(char **array, int size)
{
    char temp[MAX_FILE];
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (get_timestamp(array[j]) < get_timestamp(array[j + 1])) // if a < b, swap the strings
            {
                my_strcpy(temp, array[j]);
                my_strcpy(array[j], array[j+1]);
                my_strcpy(array[j+1], temp);
            }
        }
    }
}


/* Sorting files by time last modified to mimic ls -t command. If timestamps are equal, comparing file names in alphabetical order */
void sort_dir_content_by_time(dir_c *array, int array_len)
{
    for(int i = 0; i < array_len - 1; i++)
    {
        for(int j = 0; j < array_len - i - 1; j++)
        {
            // Compare timestamps, and swap positions, if needed; for descending order - '<', for ascending order '>'
            if(array[j].timestamp < array[j+1].timestamp)
            {
                dir_c temp;
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
            // Compare file names in alphabetical order if timestamps are equal
            else if (array[j].timestamp == array[j+1].timestamp && my_strcmp(array[j].file_name, array[j+1].file_name) > 0)
            {
                dir_c temp;
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}


/* Sorting in an alphabetical order */
void sort_array_alph(char **array, int size)
{
    char temp[MAX_FILE];

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            //if the first non-matching character in str1 is greater (in ASCII) than that of str2
            if (my_strcmp(array[j], array[j+1]) > 0) 
            {
                my_strcpy(temp, array[j]);
                my_strcpy(array[j], array[j+1]);
                my_strcpy(array[j+1], temp);
            }
        }
    }
}


/* Creates a full path by concatenating directory and file name, required for lstat() */
char* create_full_path(char* directory, char* dir_entry)
{
    int directory_len = my_strlen(directory);
    int dir_entry_len = my_strlen(dir_entry);

    // Allocate memory for the full path (+1 for the directory separator and +1 file name, and +1 for the null terminator))
    char* full_path = malloc((directory_len + dir_entry_len + 3) * sizeof(char));
    if (full_path == NULL)
    {
        printf("Failed to allocate memory for the full_path.\n");
        return NULL;
    }
    if (my_strcmp(directory, ".") == 0 && my_strcmp(dir_entry, "..") != 0)
    {
        my_strcpy(full_path, dir_entry);
    }
    else
    {
        my_strcpy(full_path, directory);

        if (directory_len > 0 && directory[directory_len - 1] != '/')
        {
            my_strcat(full_path, "/");
        }
        my_strcat(full_path, dir_entry);
    }
    return full_path;
}


/* List contents of the directory if there is only one directory given as CL input */
void list_dir (char *path, int flag, int op_a, int op_t)
{
    DIR *directory = opendir(path);
    if (directory == NULL)
    {
        printf("Unable to read a directory.\n");
        return;
    }
    struct dirent *entry;
    char **array = (char**)malloc(MAX_SIZE*sizeof(char*)); // An array to store the directory contents
    if (array == NULL)
    {
        printf("Failed to allocate memory.\n");
        return;
    }
    int size = 0;

    dir_c *dir_array = malloc(MAX_SIZE*sizeof(dir_c)); // A struct array for option -t content names and timestamps
    if (dir_array == NULL)
    {
        printf("Failed to allocate memory.\n");
        return;
    }
    int count = 0;

    if (op_a)
    {
        flag = 1;
    }


    while ((entry = readdir(directory)) != NULL)
    {
        if (flag == 0 && entry->d_name[0] == '.')
        {
            continue;
        }

        if (op_t)
        {
            struct stat fileinfo;
            char* full_path = create_full_path(path, entry->d_name);
            int result = lstat(full_path, &fileinfo);

            if (result == 0)
            {
                my_strcpy(dir_array[count].file_name, entry->d_name);
                //dir_array[count].timestamp = (fileinfo.st_mtim.tv_sec * 1e9) + fileinfo.st_mtim.tv_nsec; // for DoCode
                dir_array[count].timestamp = fileinfo.st_mtime * 100000000; //NOTE: the older C library versions use: fileinfo.st_mtime | for VSCode
                count++;
            }
        }
        else 
        {
            array[size] = (char*)malloc((MAX_FILE + 1)*sizeof(char)); // memalloc for each string inside the array
            my_strcpy(array[size], entry->d_name);
            size++;
        }
        
    } 
    
    if (op_t)
    {
        sort_dir_content_by_time(dir_array, count);
        for (int i = 0; i < count; i++)
        {
            printf("%s\n", dir_array[i].file_name);
        }
        free(dir_array);
    }
    else
    { 
        sort_array_alph(array, size);
        print_array(array, size);
        free_strings(array, size);
        free(array);
    }
    closedir(directory);
}


/* If input is multiple directories, list these in alphabetical order by default (unless: option -t), 
*  each printed as "dir:" and a newline before each directory, after the first directory 
*/
void list_mult_dir(char **array, int size, int flag, int op_a, int op_t)
{
    int first_dir = 1; // Flag to keep track of first printed directory
    for (int j = 0; j < size; j++)
    {
        if(!first_dir)
        {
            printf("\n"); // Print newline before printing directory title
            printf("%s:\n", array[j]);
        }
        else 
        {
            printf("%s:\n", array[j]);
            first_dir = 0; // Set flag to 0 after printing first directory title
        }
        list_dir(array[j], flag, op_a, op_t); // contents
    }     
}


/* Processing options/flags (-t, -a) based on the number of args/operands entered as CL input after the options/flags */
void send_op(int ls_time, int ls_hidden, int flag, char *path, char **array, int size)
{
    if (size == 0)
    {
        path = ".";
        list_dir(path, flag, ls_hidden, ls_time);
    }
    else if (size == 1)
    {
        path = array[0];
        list_dir(path, flag, ls_hidden, ls_time);
    }
    else if (size > 1)
    {
        if (ls_time)
        {
            sort_cl_input_by_time(array, size);
        }
        else
        {
            sort_array_alph(array, size);
        }
        list_mult_dir(array, size, flag, ls_hidden, ls_time);
    }
}


/* Processing args/operands based on the number of args/operands entered as CL input (if there is more than 1 directory, dir displayed with ':') */
void send_args(int ls_time, int ls_hidden, int flag, char *path, char **array, int size)
{
    if (size == 1)
    {
        path = array[0];
        list_dir(path, flag, ls_hidden, ls_time);
    }
    else if (size > 1)
    {
        sort_array_alph(array, size);
        list_mult_dir(array, size, flag, ls_hidden, ls_time);
    }
}