#include "ls.h"

void _ls(char* path, bool r)
{
    if (r) printf("%s:", path);                                                     

    DIR *dir = opendir(path);                                                       
    struct dirent *sd;                                                          

    int fileCount = getFileCount(path);                                                                              
    file_array* files = init_files(fileCount);                                      
    
    if (r && files->size !=0) printf("\n");                                         

    int index = 0;
    while ((sd = readdir(dir)) != NULL)                                                                            
    {    
        if (is_regular_file(sd->d_name))                                            
        {
            add_to_array(&files->array[index], sd->d_name);                         
            index++;                                                            
        }
    }
    sort_files(&files, false);                                                       
    print_files(files);                                                            
    if (r) ls_r(files, path, false, false);
    
    free_files(files);                                                               
    closedir(dir);                                                      
}