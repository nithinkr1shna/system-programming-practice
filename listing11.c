#include<stdio.h>
#include<unistd.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

int main(){

  int pid,status =0;
  long dat=0;
  //int dat =0;
  void  *addr;
  if((pid = fork())== 0){
    ptrace(PTRACE_TRACEME, 0,0,0);
    execl("/home/wolf/qstns_sys_programming/child5","child5", (char *)0);
    printf("execl failed\n");
  }
  else{
    wait(&status);
     while(1) {
     // do just one instruction
       ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
       wait(&status);
       if(WIFEXITED(status))
	 break;
       // `addr' is address of `i' in child process
       dat = ptrace(PTRACE_PEEKDATA, pid, addr, 0);
      if(dat == 10) {
           ptrace(PTRACE_POKEDATA, pid, addr, 2341);
           ptrace(PTRACE_CONT, pid, 0, 0);
           break;
      }
    }
   wait(&status);
  if(WIFEXITED(status))
   printf("child over\n");
 }

}
