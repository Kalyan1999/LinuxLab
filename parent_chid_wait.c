#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//for fork(),getpid(),getppid() etc..
#include <sys/wait.h> //for wait() related function calls..
int main( )
{
int child_pids[5];
int i;
for(i=0;i<5;i++)
{
if(fork()==0)
{
printf("child(pid): %d of parent(pid): %d\n",getpid(),getppid());
exit(0);
}
}
for(i=0;i<5;i++)
{
int cpid=wait(NULL);
printf("parent (pid): %d waited for child(pid): %d\n",getpid(),cpid);
}
return 0;
}
