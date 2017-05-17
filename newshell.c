#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>


char **tokenize(char **args);
int launch_shell(char **args);
void set_global_flags(char **args);
void execute_cmd(char **args);

char input[64],output[64], from[64][64], to[100][100];
int in=0, out=0,flag_pipe =0, p[2];


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
  set_global_flags(string);
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

  
  
  if(pid == 0){
    // is the child process

    if(flag_pipe){

      pipe(p);
      close(0);
      close(p[0]);
      close(p[1]);
      dup2(p[0],0);
      execute_cmd((char **)to);
      
    }
    
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
    //for single commands
    execute_cmd(args);
  }
 
}


void execute_cmd(char **args){

  if (execvp(args[0],args)== -1)
      perror("Error executing newshell.c in exec");
  
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


char **to_pointer = (char **)to;
char **from_pointer = (char **)from;
// set global flag for redirection
void set_global_flags(char **args){

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
    else if(strcmp(*args,"|") == 0){
      *args = NULL;
      flag_pipe =1;
      ++args;
      printf("pipe present \n");
     
      
      while(*args != NULL){
        //to
	if(strcmp(*args,">")==0 || strcmp(*args,"|")==0 || strcmp(*args, "<")){
	  args--;
	  printf("break on\n");
	  break;
	}
        *to_pointer = *args; 
         printf("after pipe: %s\n", *to_pointer);

	 args++;
	 to_pointer++;
      }
      //args--;
      //args--;
    }
     else if(strcmp(*args, "|") != 0 && *args != NULL){

      //from
      while(*args != NULL){
	if(strcmp(*args,"|")==0 || strcmp(*args,"<")==0 || strcmp(*args,">")==0){

	  //args--;
	  break;
	}
        printf("before %s\n",*args);
	*from_pointer = *args;
	args++;
	from_pointer++;

	
      }
	 args--;
      
	 }
    args++;
  }
  
}
