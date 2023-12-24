#include "ls.h"

void ls_a(char *path, bool r, bool t)
{
    if (r) printf("%s:\n", path);

    DIR *dir = opendir(path);
    struct dirent *sd;
    
    if (dir == NULL) return;

    int fileCount = getFileCount(path) + hidden_fileCount(path);                            
    if (t == true) fileCount += 2;                                                          
    file_array* files = init_files(fileCount);  
    
    int index = 0;                                                                                             
    char* filepath;
    while ((sd = readdir(dir)) != NULL)                                                     
    {   
        if (!t && is_curr_par_dir(sd->d_name)) continue;                                     
        add_to_array(&files->array[index], sd->d_name);                 
        filepath = is_curr_par_dir(sd->d_name) ? sd->d_name : get_filepath(path, sd->d_name);
        if (t) assign_times(&files->array[index], filepath);
        if (!is_curr_par_dir(sd->d_name)) free(filepath);
        index++;                                                       
    }
    sort_files(&files, t);
    
    if (!t) printf(".  ..  ");                                                               
    print_files(files);

    if (r) ls_r(files, path, true, t);                                                       
    
    free_files(files);
    closedir(dir);                                                        
}