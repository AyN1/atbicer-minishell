#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t childPid;

    printf("Before fork %d\n", getpid());

    // fork creates a child and returns its process ID
    childPid = fork();

    printf("After fork %d\n", getpid());
    exit(0);
}
