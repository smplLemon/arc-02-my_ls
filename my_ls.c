#include "ls.h"                

void run(int argc, const char* argv[])
{
    bool r = false;                                                                     
    bool a = false;
    bool t = false;                                                         
    bool empty_path = true;                                                             
    int index = 0;
    int dirCount = 0;                                                                   

    string_array* path = init_array(argc - 1);
    for (int i = 1; i < argc; i++)
    {
        if (is_option(argv[i]))                                                         
        {                                                      
            if (get_options(argv[i], &r, &a, &t) != 0)                                     
            {                                                                           
                free_string_array(path);                                               
                return;
            }
        }
        else
        {
            empty_path = false;                                                         
            path->array[index] = (char*)malloc(sizeof(char) * my_strlen(argv[i]));     
            my_strcpy(path->array[index], argv[i]);                                     
            index++;                                                                      
            dirCount++;                                                                
        }
    }

    if (!empty_path)                                                                    
    {                                                                
        for (int i = 0; i < dirCount; i++)                                              
        {                                          
            if (dirCount != 1) printf("%s:\n", path->array[i]);                         
            my_ls(path->array[i], r, a, t);                                            
            if (i != dirCount - 1) printf("\n\n");                                      
            else printf("\n");                                                       
        }
    }
    else
    {
        my_ls(CURRENT_DIR, r, a, t);                                                    
    }
    free_string_array(path);                                                            
}

void my_ls(char *path, bool r, bool a, bool t)
{
    DIR *dir = opendir(path);                                                                                                                                                                     
    if (dir == NULL)                                                                   
    {                                                                    
        if (isFile(path)) printf("%s", path);                                           
        else printf(NO_FILE, path);                                                     
        return;                                                                         
    }
    closedir(dir);                                                                      
    if (a)                                                                             
    {                     
        ls_a(path, r, t);                                                               
    }
    else
    {                      
        if (t) ls_t(path, r);                                                           
        else  _ls(path, r);                                                             
    }
    if (!r && !a && !t) printf("\n");                                                   
}