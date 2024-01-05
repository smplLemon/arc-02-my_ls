#include "my_ls.h"


int set_flags(int ac, char** av, bool* flag_a, bool* flag_t) {
    if (ac == 2) {
        if (my_str_eql(av[1], "-a")) {
            *flag_a = true;
        } else if (my_str_eql(av[1], "-t")) {
            *flag_t = true;
        } else if (my_str_eql(av[1], "-at") || my_str_eql(av[1], "-ta")) {
            *flag_a = true;
            *flag_t = true;
            return 1;
        }
    } else if (ac >= 3) {
        if (my_str_eql(av[1], "-a")) {
            *flag_a = true;
        } else if (my_str_eql(av[1], "-t")) {
            *flag_t = true;
        } else if (my_str_eql(av[1], "-at") || my_str_eql(av[1], "-ta")) {
            *flag_a = true;
            *flag_t = true;
            return 1;
        }

        if (my_str_eql(av[2], "-a") && !*flag_a) {
            *flag_a = true;
        } else if (my_str_eql(av[2], "-t") && !*flag_t) {
            *flag_t = true;
        }
        
    } 
    return (int) *flag_a + (int) *flag_t;
}

void swap(char* str1, char* str2) {
    char temp[MAX_LEN];
    my_str_copy(temp, str1);
    my_str_copy(str1, str2);
    my_str_copy(str2, temp);
}

void timelex_sort(char* dir_str, char* first, char* second) {

    struct stat buffer;
    struct stat buffer2;
    char dir_str_copy[MAX_LEN] = "";
    char dir_str_copy2[MAX_LEN] = "";
    my_str_cat(dir_str_copy, dir_str);
    my_str_cat(dir_str_copy, "/");
    my_str_cat(dir_str_copy2, dir_str);
    my_str_cat(dir_str_copy2, "/");

    my_str_cat(dir_str_copy, first);
    lstat(dir_str_copy, &buffer);
    __time_t sec = buffer.st_mtim.tv_sec;
    __time_t nsec = buffer.st_mtim.tv_nsec;

    my_str_cat(dir_str_copy2, second);
    lstat(dir_str_copy2, &buffer2);
    __time_t sec2 = buffer2.st_mtim.tv_sec;
    __time_t nsec2 = buffer2.st_mtim.tv_nsec;
    
    if (sec2 > sec) {
        swap(first, second);
    } else if (sec2 == sec && nsec2 > nsec) {
        swap(first, second);
    } else if (sec2 == sec && nsec2 == nsec) {
        if (my_str_cmp(first, second) > 0) {
            swap(first, second);
        }   
    }
}

void lex_or_timelex_sort(char* dir_str, char array[][MAX_LEN], int str_count, bool flag_t) {
    for (int i = 0; i < str_count - 1; i++) {
        for (int j = 0; j < str_count - i - 1; j++) {
            if (flag_t) {
               timelex_sort(dir_str, array[j], array[j+1]);
            } else {
                if (my_str_cmp(array[j], array[j+1]) > 0) {
                    swap(array[j], array[j + 1]);
                }
            }
        }
    }
}

void set_all_files_and_dirs_count(int* file_count, int* dir_count, int count_flags, int ac,  char av[][MAX_LEN]) {
    DIR* dir;
    for (int index_operand = count_flags+1; index_operand < ac; index_operand++) {
        dir = opendir(av[index_operand]);
        if (dir == NULL) {
            *file_count = *file_count + 1;
        } else {
            *dir_count = *dir_count + 1;
        }
        closedir(dir);
    }
}

void fill_file_and_dir_arrays(char files[][MAX_LEN], char dirs[][MAX_LEN], int count_flags, int ac, char av[][MAX_LEN]) {
    DIR* dir;
    int file_index = 0;
    int dir_index = 0;
    for (int index_operand = count_flags+1; index_operand < ac; index_operand++) {
        dir = opendir(av[index_operand]);
        if (dir == NULL) {
            my_str_copy(files[file_index], av[index_operand]);
            file_index++;
        } else {
            my_str_copy(dirs[dir_index], av[index_operand]);
            dir_index++;
        }
        closedir(dir);
    }
}

void set_dir_count(int* dir_count, char* dir_str, bool flag_a) {
    struct dirent* entry;
    DIR* dir = opendir(dir_str);

    while ((entry = readdir(dir)) != NULL) {
        char* name = entry->d_name;
        if (!flag_a && name[0] == '.') {
            continue;
        }
        *dir_count = *dir_count + 1;
    }
    closedir(dir);
}

void fill_dir_array(char files[][MAX_LEN], char* dir_str, bool flag_a) {
    struct dirent* entry;
    DIR* dir = opendir(dir_str);
    int dir_index = 0;

    while ((entry = readdir(dir)) != NULL) {
        char* name = entry->d_name;
        if (!flag_a && name[0] == '.') {
            continue;
        }
        my_str_copy(files[dir_index], name);
        dir_index++;
    }
    closedir(dir);
}

void print_dir_entries(char* dir_str, bool flag_a, bool flag_t) {
    int dir_count = 0;
    set_dir_count(&dir_count, dir_str, flag_a);
    char dir_array[dir_count][MAX_LEN];
    fill_dir_array(dir_array, dir_str, flag_a);
    lex_or_timelex_sort(dir_str, dir_array, dir_count, flag_t);
    print_str_array(dir_array, dir_count);
}

int main(int ac, char** av) {
    bool flag_a = false;
    bool flag_t = false;
    int all_files_count = 0;
    int all_dirs_count = 0;

    
    int count_flags = set_flags(ac, av, &flag_a, &flag_t);

    bool has_operands = ac > count_flags + 1;
    if (has_operands) {
        char arguments[ac][MAX_LEN];
        for (int i = 0; i < ac; i++) {
            my_str_copy(arguments[i], av[i]);
        }
        set_all_files_and_dirs_count(&all_files_count, &all_dirs_count, count_flags, ac, arguments);
        char all_files_array[all_files_count][MAX_LEN];
        char all_dirs_array[all_dirs_count][MAX_LEN];
        fill_file_and_dir_arrays(all_files_array, all_dirs_array, count_flags, ac, arguments);

        lex_or_timelex_sort(".", all_files_array, all_files_count, flag_t);      

        print_str_array(all_files_array, all_files_count);
        if (all_files_count > 0) {
            printf("\n");
        }

        lex_or_timelex_sort(".", all_dirs_array, all_dirs_count, flag_t);
        for (int i = 0; i < all_dirs_count; i++) {
            char* dir = all_dirs_array[i];
            if (all_dirs_count > 1) {
                printf("%s:\n", dir);
            }
            print_dir_entries(dir, flag_a, flag_t);
            if (i < all_dirs_count - 1) {
                printf("\n");
            } 
        }

    } else {
        print_dir_entries(".", flag_a, flag_t);
    }
}