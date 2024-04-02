# Task

To create an implementation of command called ls that is part of the Unix-like operating systems.

# Description

In this project, I created some functions that are:
• int my_strcmp() - to get options written on terminal, if they are equal to 0, it works properly as an option;
• void my_linked_list_swap() - it swaps linked list if the previous one is greater than next one;
• void sort_by_time() -this function created for -t option that swaps given files and folders by last access time;
• void sort_by_ascii() - to print all files and folders by ascii table order;
• void free_linked_list() - created to free linked lists to get rid of memory leaks;
• void print_linked_list() - this function prints every linked list that is connected;
• void add_node() -  it adds and creates new node for the next;
• void open_directory() -  it opens files and directories with opendir(), readdir() and closes with closedir() function.
• void control() -  it is created to control all options and opening file, folders;
• void my_options() - the function where I geather all my options.
The main function int main(int argc, char **argv) does the main work in the implementation of ls project.

# Installation

Write make on terminal which will create other files via Makefile to check weahter it is working or no

# Usage

Call ./my_ls and 'filename' 'foldername' and '-a; -t; -at; -ta' options or ./my_ls '-a; -t; -at; -ta' options without 'filename' and 'foldername'
