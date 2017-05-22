/* `tracer' parent */
#include <stdio.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    int pid, status;
    if((pid = fork()) == 0) {
      execl("/home/wolf/qstns_sys_programming/listing1", "listing1", (char *)0); //check man page of execl
        printf("exec failed...\n");
    } else {
        sleep(1);
        kill(pid, SIGINT); // kill the child using kill
        wait(&status); // wait for child to stop
        if(WIFSTOPPED(status))
            printf("child has stopped...\n");
        sleep(3);
        ptrace(PTRACE_CONT, pid, 0, 0); // restart the stopped child
        /* Will not come out of this wait because
         * child does not terminate.
         */
        wait(&status); 
    }
}
        
// explanation:
//~~~~~~~~~~~~~

// parent creates a child process, child executes the program listing1,
// parent sleeps for 1 ms and kills the child process
// and wait for child to die..
// confirms child is stopped by using WIFSTOPPED
// the parent slleps for 3 ms
// parent restarts the child process again, this time parent wont kill the child and hence the child executes , indefinitley as the child defined.
// the parent waits for the child to end , but this waiting is inifinite, coz the child runs for inifinite time.
