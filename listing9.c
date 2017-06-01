#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/user.h>
//segment of code which alters value of
//a variable in a child process. Identical
//to code which reads and changes register value.

//`addr' is address of variable being accessed.
int main(){

  int pid,data, status=0,addr,dat;
  struct user_regs_struct uregs;
  
  if((pid =fork())==0){

      ptrace(PTRACE_TRACEME,0,0,0);
      execl("/home/wolf/qstns_sys_programming/listing8", "listing8", (char *)0);

  }else {
    
      sleep(10);
      kill(pid,SIGINT);
      wait(&status);
      data= ptrace(PTRACE_PEEKDATA, pid,0x601048, 0); // addr passes is the address of i in child.
      printf("data = %d\n", data);
      data = 245;
      ptrace(PTRACE_POKEDATA, pid, 0x601048, data);
      ptrace(PTRACE_CONT, pid, 0, 0); 
      wait(&status);
 }
}
