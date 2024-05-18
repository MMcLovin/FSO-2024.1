#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
// unistd.h is a POSIX system library, so in windows VsCode it shows as an error. It is also the lib that contains functions like and getpid()
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int calls = 0;

int main ()
{
    // I dont get this, every time I run a program a new process is created? bc I didnt create a new process here. I think I understant it now, a process is created to run my code!
    pid_t my_first_ever_pid = getpid();
    // If I create another process from this point on, it will also execute all the code from this point on, just as it's parent, including the creation of a new process, through fork, with a new pid.
    pid_t child = fork();

    printf("PID is: %d\n", getpid());

    // list all processes
    system("ps -l");
    return 0;
}