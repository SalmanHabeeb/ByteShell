# ByteShell

ByteShell is a simple Linux shell that supports basic commands and some additional features.

## Features

- Store history and access it using `history` command
- Create alias for a command using `alias` command
- Other inbuilt commands like `cd`, `help`, `show license`, and `exit`

## Usage

To compile the shell, run `gcc *.c -o main.exe` in the project directory. This will generate an executable file named `main.exe`.

To run the shell, run `./main.exe` in the project directory. This will start the shell prompt, where you can enter commands.

To exit the shell, enter `exit` or press Ctrl-C.

## How the project works

A shell is a program that takes commands from the user and executes them by invoking other programs or built-in functions. A shell also provides features such as history, alias, redirection, piping, and scripting.

To make a shell in C language, you need to use some system calls and library functions that interact with the operating system and the file system. You also need to implement some logic and data structures to parse, store, and execute the commands.

The main steps of making a shell in C language are:

- Create an infinite loop that reads input from the user and prints a prompt
- Parse the input into tokens and separate them by spaces, quotes, or special characters
- Check if the input is empty, a built-in command, or an external command
- If the input is a built-in command, execute it using a function or a system call
- If the input is an external command, fork a child process and execute it using execvp or another variant of exec
- Wait for the child process to finish and return the status
- Repeat until the user enters exit or presses Ctrl-C

## References

 [Making your own Linux Shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)
 [Tutorial to code a simple shell in C](https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e)
 [Simple shell in C](https://gist.github.com/parse/966049)
 [Shell in the C Programming language](https://stackoverflow.com/questions/8006218/shell-in-the-c-programming-language)