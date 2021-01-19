#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


pid_t cpid;
pid_t ppid;
void my_handler(int signum)
{
int status;
waitpid(cpid,&status,0);
if(WIFEXITED(status))
{
int exit_status=WEXITSTATUS(status);
printf("Exit status of the child was %d from handler!\n",exit_status);
}
}
int main( )
{
signal(SIGUSR1, my_handler);
printf("hi from parent!\n");
if((cpid=fork())==0)
{
printf("hi from child!!\n");
ppid=getppid();
kill(ppid,SIGUSR1);
exit(0);
}
else
{
wait(NULL);
}
}
