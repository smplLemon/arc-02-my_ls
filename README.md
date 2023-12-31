# Description

In computing, ls is a command to list computer files and directories in Unix and Unix-like operating systems. It is specified by POSIX and the Single UNIX Specification.

It is available in the EFI shell,[1] as a separate package for Microsoft Windows as part of the UnxUtils collection of native Win32 ports of common GNU Unix-like utilities,[2] or as part of ASCII's MSX-DOS2 Tools for MSX-DOS version 2.[3]

The numerical computing environments MATLAB and GNU Octave include an ls function with similar functionality.[4][5]

In other environments, such as DOS, OS/2, and Microsoft Windows, similar functionality is provided by the dir command.

# Task

Unix and Unix-like operating systems maintain the idea of a working directory. When invoked without arguments, ls lists the files in the working directory. If a directory is specified as an argument, the files in that directory are listed; if a file is specified, that file is listed. Multiple directories and files may be specified.

In many Unix-like systems, names starting with a dot (.) are hidden. Examples are ., which refers to the working directory, and .., which refers to its parent directory. Hidden names are not shown by default. With -a, all names, including all hidden names, are shown. Using -A shows all names, including hidden names, except for . and ... File names specified explicitly (for example ls .secret) are always listed.

# Installation
./make
./my_ls.c

# Usage