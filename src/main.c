#include <sys/stat.h>       // for stat(), lstat()
#include <stdlib.h>         // for malloc(), free()
#include "ls.h"
#include "utils.h"


int main(int ac, char **av)
{
    char *path;
    int flag = 0; //no hidden files by default
    int ls_hidden = 0;
    int ls_time = 0;
    if (ac == 1 && my_strcmp(av[0], "./my_ls") == 0)                          
    {
        path = ".";
        list_dir(path, flag, ls_hidden, ls_time);
    }

    /* if ac > 1 files displayed first, files displayed in alph order, files and dir to be sorted separately */

    // An array to store the directories entered as CL input
    char **d_array = (char**)malloc(MAX_SIZE*sizeof(char*));
    int d_size = 0;


    // An array to store the files entered as CL input  
    char **f_array = (char**)malloc(MAX_SIZE*sizeof(char*));
    int f_size = 0;

    struct stat buf;

    for (int i = 1; i < ac; i++)
    {
        if (av[i][0] != '-' && (check_input(ac, av[i])))
        {
            if(stat(av[i], &buf) == 0)
            {
                if(S_ISDIR(buf.st_mode))
                {
                    d_array[d_size] = (char*)malloc((my_strlen(av[i]) + 1)*sizeof(char)); 
                    my_strcpy(d_array[d_size], av[i]);
                    d_size++;
                }
                else if(S_ISREG(buf.st_mode))
                {
                    f_array[f_size] = (char*)malloc((my_strlen(av[i]) + 1)*sizeof(char)); 
                    my_strcpy(f_array[f_size], av[i]);
                    f_size++;

                }
            }
        }
    }


    // options
    ls_options *op = check_op(ac, av);

    if (op->t && op->a)                                                                   
    {
        ls_time = 1; 
        ls_hidden = 1;
        flag = 1;
        send_op(ls_time, ls_hidden, flag, path, d_array, d_size);
    }
    else if (op->a)
    {
        ls_hidden = 1; 
        flag = 1;
        send_op(ls_time, ls_hidden, flag, path, d_array, d_size);
    }
    else if (op->t)
    {
        ls_time = 1;
        send_op(ls_time, ls_hidden, flag, path, d_array, d_size);
    }
    else
    {
        if (f_array)
        {
            sort_array_alph(f_array, f_size);
            print_array(f_array, f_size);
            free_strings(f_array, f_size);
            free(f_array);
        }

        send_args(ls_time, ls_hidden, flag, path, d_array, d_size);
    }

    free_strings(d_array, d_size);
    free(d_array);

    return 0;
}
