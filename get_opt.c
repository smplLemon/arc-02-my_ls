# include "ls.h"

// Function to check if given argument is option starting with '-'
bool is_option(const char* arg)
{
    return arg[0] == '-';
}

// Function to parse the option list
int get_options(const char* arg, bool* r, bool* a, bool* t)
{
    char* option = (char*)(arg + 1);                                      
    while (*option != '\0')
    {                                                 
        if (*option == 'R')
        {
            *r = true;                                                       
        }
        else if (*option == 'a')
        {
            *a = true;                                                       
        }
        else if (*option == 't')
        {
            *t = true;                                                       
        }
        else
        {                                                  
            printf(INVALID_OPT, *option);              
            printf(TRY_HELP);
            return -1;
        }
        option++;                                                          
    }
    return 0;
}