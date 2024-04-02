#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct ls_listnode
{
    char *name;
    struct ls_listnode *next;
} list;

typedef struct u_input
{
    list *files;
    list *directs;
} input;

int my_strcmp(char *str1, char *str2)
{
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return (int)(str1[i] - str2[i]);
        }
        i++;
    }
    return 0;
}

void free_linked_list(list **head)
{
    list *curr = *head;
    while (curr != NULL)
    {
        list *temp = curr;
        curr = curr->next;
        free(temp->name);
        free(temp);
        temp = curr;
    }
    *head = NULL;
}

void add_node(list **head, char *name)
{
    list *temp = (list *)malloc(sizeof(list));
    temp->name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(temp->name, name);
    temp->next = NULL;

    if (*head == NULL)
    {
        *head = temp;
    }
    else
    {
        list *curr = *head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = temp;
    }
}

void my_linked_list_swap(char **s1, char **s2)
{
    char *tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

void sort_by_ascii(list *head)
{
    list *temp2 = NULL;
    list *temp1 = head;

    while (temp1 != NULL)
    {
        temp2 = temp1->next;
        while (temp2 != NULL)
        {
            if (my_strcmp(temp1->name, temp2->name) > 0)
            {
                my_linked_list_swap(&(temp1->name), &(temp2->name));
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

void sort_by_time(list *head)
{

    list *temp2 = NULL;
    list *temp1 = head;

    struct stat fs1;
    struct stat fs2;

    while (temp1 != NULL)
    {
        temp2 = temp1->next;
        while (temp2 != NULL)
        {
            stat(temp1->name, &fs1);
            stat(temp2->name, &fs2);
            if (fs1.st_mtim.tv_sec == fs2.st_mtim.tv_sec)
            {
                if (fs1.st_mtim.tv_nsec < fs2.st_mtim.tv_nsec)
                {
                    my_linked_list_swap(&(temp1->name), &(temp2->name));
                }
            }
            else if (fs1.st_mtim.tv_sec < fs2.st_mtim.tv_sec)
            {
                my_linked_list_swap(&(temp1->name), &(temp2->name));
            }

            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
}

void print_linked_list(list *head, int flag)
{
    list *current = head;
    while (current)
    {
        if (flag == 0 || flag == 2)
        {
            if (current->name[0] != '.')
            {
                printf("%s\n", current->name);
            }
        }
        else
        {
            printf("%s\n", current->name);
        }
        current = current->next;
    }
}

void check_sort(list *head, int flag)
{
    if (flag == 1 || flag == 0)
    {
        sort_by_ascii(head);
    }
    else
    {
        sort_by_time(head);
    }
}

void open_directory(char *dirname, int flag)
{
    DIR *direct;
    direct = opendir(dirname);

    struct dirent *data;
    list *content = NULL;
    while ((data = readdir(direct)) != NULL)
    {
        add_node(&content, data->d_name);
    }
    check_sort(content, flag);
    print_linked_list(content, flag);
    closedir(direct);
    free_linked_list(&content);
}

void control(input *us_input, int flag)
{
    if (!us_input->files && !us_input->directs)
    {
        open_directory(".", flag);
    }
    if (us_input->files)
    {
        list *files = us_input->files;
        check_sort(files, flag);
        print_linked_list(files, flag);
    }
    if (us_input->directs)
    {
        int point = 0;
        if (us_input->directs->next)
        {
            point = 1;
        }
        if (us_input->files)
        {
            printf("\n");
            point = 1;
        }
        check_sort(us_input->directs, flag);
        list *head = us_input->directs;
        while (head)
        {
            if (point)
            {
                printf("%s:\n", head->name);
            }
            open_directory(head->name, flag);
            if (head->next)
            {
                printf("\n");
            }
            head = head->next;
        }
    }
}

void my_options(int argc, char **argv)
{
    int a = 0;
    int t = 0;
    input *us_input = (input *)malloc(sizeof(input));
    us_input->files = NULL;
    us_input->directs = NULL;
    for (int i = 1; i < argc; i++)
    {
        if (my_strcmp(argv[i], "-a") == 0)
        {
            a = 1;
        }
        else if (my_strcmp(argv[i], "-t") == 0)
        {
            t = 1;
        }
        else if ((my_strcmp(argv[i], "-at") && my_strcmp(argv[i], "-ta")) == 0)
        {
            t = 1;
            a = 1;
        }
        else
        {
            if (open(argv[i], O_RDONLY) <= 0)
            {
                printf("ls: cannot access '%s': No such file or directory\n", argv[i]);
            }
            else
            {
                struct stat mode;
                stat(argv[i], &mode);
                if (S_ISREG(mode.st_mode))
                {
                    add_node(&(us_input->files), argv[i]);
                }
                else
                {
                    add_node(&(us_input->directs), argv[i]);
                }
            }
        }
    }

    int flag = 0;
    if (a && t)
    {
        flag = 3;
    }
    else if (a)
    {
        flag = 1;
    }
    else if (t)
    {
        flag = 2;
    }
    control(us_input, flag);
}

int main(int argc, char **argv)
{
    my_options(argc, argv);
    return 0;
}