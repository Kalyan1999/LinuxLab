#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void forktest( )

{
int a=3,b=2;
if(fork( )==0)
{
a=a+1;
b=b+1;
_exit(1);
}
int cid=wait(NULL);
printf("fork: a: %d b: %d\n",a,b);
}
void vforktest( )
{
int a=3,b=2;
if(vfork( )==0)
{
a=a+1;
b=b+1;
_exit(2);
}
int cid=wait(NULL);
printf("vfork: a: %d b:%d\n",a,b);
}
int main( )
{
forktest( );
vforktest( );
return 0;
}
