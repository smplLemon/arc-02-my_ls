#include "ls.h"

int main(int argc, const char* argv[])
{
    if (argc == 1)
    {
        my_ls(CURRENT_DIR, false, false, false);                                                
    }
    else
    {
        run(argc, argv);                                                                        
    }
    return 0;
}