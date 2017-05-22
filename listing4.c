#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <unistd.h>
int main()
{
    int pid, status;
    if((pid = fork()) == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execl("/home/wolf/qstns_sys_programming/listing5", "listing5", (char *)0);
        printf("exec failed...\n");
    } else {
        wait(&status);
        if(WIFSTOPPED(status))
            printf("child has stopped...\n");
        sleep(10);
        ptrace(PTRACE_CONT, pid, 0, 0);
        wait(&status);
    }
    return 0;
}


//explanatuon:
//~~~~~~~~~~~

//parent process creates a child, child run ptrace => so the
// child now can be traced by the parent. The execl executes any
// arbitary child. If the ptrace was in the child source then only that
// child can be traced for example,
// if there are 3 child and , child1 has ptrace in its code, then only
// that child cna be traced by the parent
// but in here the ptrace is for the child of the parent process, this
// child can be child1, child2, child3. Hence any of the process can be
// executed as the child and can be traced. 
