#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>

int main()
{ 
  int pid;
  int fds[2];
  
  if(pipe(fds) == -1)
  { 
    printf("pipe error");
   }
   
  pid = fork();
  
  if(pid == 0)
  {
     close(fds[0]);
     dup2(fds[1],STDOUT_FILENO);
     execlp("ls","ls",NULL);
  }
  else
   {
      int status;
      wait(&status);
      close(fds[1]);
      dup2(fds[0],STDIN_FILENO);
      execlp("wc","wc","-l","-c","-w",NULL);
    }
   }
