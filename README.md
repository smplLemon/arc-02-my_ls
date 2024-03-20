# Task

To create an implementation of command called ls that is part of the Unix-like operating systems.

# Description

In this porject I created some functions that are:
• int my_strcmp() - to get options written on terminal, if they are equal to 0 works properly as an option;
• void my_linked_list_swap() - it swaps linked list if the previous is greatter than next one;
• void sort_linked_list() -this function created for -t option that swaps given files and folders by last access time;
• void sort_by_ascii() - to print all files and folders by ascii table order;
• void free_linked_list() - created to free linked lists to get rid of memory leaks;
• void print_linked_list() - this function prints every linked list that is connected;
• void newline_node() -  it prints every linked list one by one from the new line, actually it does the same work as -1 in ls;
• void my_ls() -  it opens files and directories with opendir(), readdir() and closes with closedir() function.
• void control() -  it is created to control all options and opening file, folders.
The main function int main(int argc, char **argv) does main work in implementation of ls project.

# Installation

Write make on terminal which will create other files via Makefile to check weahter it is working or no

# Usage

Call ./my_ls and 'filename' 'foldername' and '-a; -t; -at; -ta' options or ./my_ls '-a; -t; -at; -ta' options without 'filename' and 'foldername'
