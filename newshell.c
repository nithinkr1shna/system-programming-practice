#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>


char **tokenize(char **args);
int launch_shell(char **args);
void set_global_redirection_flag(char **args);

char input[64],output[64];
int in=0, out=0;

int main(int argc , char **argv){

  char **string, tokenized[100];
  char *cmd;
  size_t buffsize = 1024;
  printf("Shell emulator started\n");

  cmd  = (char *)malloc(buffsize * sizeof(char));
  if(cmd = NULL)
    fprintf(stderr,"Unable to allocate\n");

  getline(&cmd,&buffsize,stdin);
  string = tokenize(&cmd);  
  set_global_redirection_flag(string);
  printf("%s",string[0]);
  launch_shell(string);

  return 0;
}


int launch_shell(char **args){

  pid_t pid;
  pid = fork();
  int fd0, fd1;

  
  if(pid < 0){ // fork  failed

    fprintf(stderr, "fork failed\n");
  }

  
  
  if(pid == 0){ // is the child process

    if(in){

       if((fd0 = open(input, O_RDONLY)) < 0){   // here input is the inputfile from the command
          perror("couldnt open file\n");


      } 
      dup2(fd0, STDIN_FILENO);
      close(fd0);
}
    else if(out){
      
      if((fd1 = creat(output, 0644)) <0){  // output to the file in the command

         perror("couldnt open file");
      }
      dup2(fd1, STDOUT_FILENO);
      close(fd1);

    }
    if (execvp(args[0],args)== -1)
      perror("Error executing newshell.c in exec");
  }
}


#define DELIM " \t\r\n\a"
#define BUFFSIZE 64

char **tokenize(char **string){

  //tokenize using whitespace as delimiter
  char **tokens= malloc(BUFFSIZE * sizeof(char *));
  char *token;
  char *current = *string;
  int index =0,i;

  if(!tokens){

    fprintf(stderr,"Error: unadble to allaocte\n");
  }
  
    token = strtok(current,DELIM);
    while(token != NULL){
      tokens[index++]= token;
      token = strtok(NULL,DELIM);
      
    }

    tokens[++index]= NULL;
    return tokens; 
}



// set global flag for redirection
void set_global_redirection_flag(char **args){

  while(*args){
    
    if (strcmp(*args,"<") == 0){
       in =1;
       *args = NULL;
       args++;
       strcpy(input, *args);
       args--;
    }
    else if(strcmp(*args,">") == 0){

      out =1;
      *args = NULL;
      args++;
     
      strcpy(output, *args);
      args--;
    }
    args++;
  }
  
}
