# arc-02-my_ls
This code is a simplified implementation of the "ls" command in Unix-like systems using the C programming language. It lists the contents of a directory and provides options to sort the files by name or by the last access time.

#Compilation and Execution
To compile the code, use a C compiler such as GCC. Execute the following command in your terminal:
gcc my_ls.c -o my_ls
After successful compilation, you can run the program by executing the generated binary file:

./my_ls [OPTIONS] [DIRECTORY]
Replace [OPTIONS] with one or more of the following:

-a: List all files and directories, including hidden ones (files starting with a dot).
-t: Sort files and directories by the last access time in ascending order.
-at or -ta: Sort files and directories by the last access time in descending order.
Replace [DIRECTORY] with the path to the directory you want to list. If no directory is provided, the current directory will be used as the default.

#Code Structure
The code is divided into several functions to handle different tasks. Here's a brief description of each function:

my_strlen: Utility function to calculate the length of a string.
my_strcmp: Utility function to compare two strings for equality.
add_data_to_end: Adds a new node with the given data to the end of the linked list.
counter_for_linked_list: Counts the number of nodes in the linked list.
my_linked_list_swap: Swaps the data of two nodes in the linked list.
sort_linked_list: Sorts the linked list based on the last access time of the files.
sort_by_time_last_access: Retrieves the last access time for each file in the linked list and sorts them.
listDirectoryContents: Lists the contents of a directory and populates the linked list with file and directory names.
checkFileType: Checks the type of a file/directory based on its path.
my_option_finder: Processes the command-line options and calls the appropriate function.
mainBrain: The main logic of the program that handles the execution flow.
main: The entry point of the program that calls mainBrain and passes the command-line arguments.
#Usage
When you run the program with the my_ls command followed by optional arguments and the directory path, it will list the contents of the specified directory. The output will be similar to the ls command in Unix-like systems.