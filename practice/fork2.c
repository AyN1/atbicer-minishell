#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int childPid;
    
    childPid = fork();
if (childPid == -1)
    perror("fork");
else if (childPid == 0)
    printf("child:  pid=%d, fork()=%d\n", getpid(), childPid);
else
    printf("parent: pid=%d, childPid=%d\n", getpid(), childPid);
}