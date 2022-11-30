# Homework Simulation Chapter 39 - Interlude: Files and Directories

In this homework, we’ll just familiarize ourselves with how the APIs described in the chapter work. To do so, you’ll just write a few different programs, mostly based on various UNIX utilities.

## Question 1

> **Stat**: Write your own version of the command line program `stat`, which simply calls the `stat()` system call on a given file or directory. Print out file size, number of blocks allocated, reference (link) count, and so forth. What is the link count of a directory, as the number of entries in the directory changes? Useful interfaces: `stat()`

**Answer:**

To run, modify the CMakeLists to allow the correct `main` to be called, and add a directory as the input parameter, for example `/Users/toby/Documents/ACADEMIC_Northeastern/2022_fall_now/cs5600_computerSystem_fall2022.nosync/Homework10-file-devices/`

And the link count increases as the number of entries increases.

## Question 2

> **ListFiles**: Write a program that lists files in the given directory. When called without any arguments, the program should just print the file names. When invoked with the `-l` flag, the program should print out information about each file, such as the owner, group, permissions, and other information obtained from the `stat()` system call. The program should take one additional argument, which is the directory to read, e.g., `myls -l directory`. If no directory is given, the program should just use the current working directory. Useful interfaces: `stat()`, `opendir()`, `readdir()`, `getcwd()`.

**Answer:**

`-l /Users/toby/Documents/ACADEMIC_Northeastern/2022_fall_now/cs5600_computerSystem_fall2022.nosync/Homework10-file-devices/`

## Question 3

> **Tail**: Write a program that prints out the last few lines of a file. The program should be efficient, in that it seeks to near the end of the file, reads in a block of data, and then goes backwards until it finds the requested number of lines; at this point, it should print out those lines from beginning to the end of the file. To invoke the program, one should type: `mytail -n file`, where `n` is the number of lines at the end of the file to print. Useful interfaces: `stat()`, `lseek()`, `open()`, `read()`, `close()`.

**Answer:**
`-5 /Users/toby/Documents/ACADEMIC_Northeastern/2022_fall_now/cs5600_computerSystem_fall2022.nosync/Homework10-file-devices/Chap39-file-intro/Chap39-file-intro.md`

## Question 4

> **Recursive Search**: Write a program that prints out the names of each file and directory in the file system tree, starting at a given point in the tree. For example, when run without arguments, the program should start with the current working directory and print its contents, as well as the contents of any sub-directories, etc., until the entire tree, root at the CWD, is printed. If given a single argument (of a directory name), use that as the root of the tree instead. Refine your recursive search with more fun options, similar to the powerful `find` command line tool. Useful interfaces: you figure it out.

**Answer**
`/Users/toby/Documents/ACADEMIC_Northeastern/2022_fall_now/cs5600_computerSystem_fall2022.nosync`
