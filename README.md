# system-programming-practice

### ptrace:
    ptrace is used for process trace. By this mechanism a parent process can observe or control the execution of another process. The exercises listingX.c and listingXX.c are various problems which uses ptrace system call. The exercise listing9.c uses PTRACE_PEEKDATA and PTRACE_POKEDATA fucntionality and modifies the value of a variable in the child. 
    
### newshell:
    This program is a toy version of a shell. The program creates a new chid process with the help of fork system call and executes the command when given using execvp system call. This implementation supports basic unix commands, piping and option for history.