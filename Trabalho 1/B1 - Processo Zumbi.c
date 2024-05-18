#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

//int calls = 0;
void handler(int signal_number)
{
//    printf("%dº Signal received: %d\n",++calls, signal_number);
}

int main ()
{
    pid_t ppid = getpid();
//    printf("PID: %d\n", ppid);

    // sa is a struct that contains the signal handler
    struct sigaction sa = {};
    
    // sa_handler contains the adress of my handler function
    sa.sa_handler = &handler;
    
    // disposition = the action that the kernel will take when the signal is received
    // sigaction first param: signal number
    // sigaction second param: the new disposition 
    // sigaction third param: previous disposition 
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    // parent process waits for the first signal, which creates a zombie process
    pause();
    pid_t zombie = fork();

    // the child process (cp) is terminated and the parent process (pp) has not yet called wait(), resulting in the pp never being informed of the cp termination and thus creating a zombie process
    if(zombie == 0) exit(0);

    // parent process waits for the second signal, which kills the zombie process
//    printf("Zombie PID: %d\n", zombie);
    pause();
//    printf("Killing zombie process with PID %d...\n", zombie);
    kill(zombie, SIGKILL);
    waitpid(zombie, NULL, 0);
//    printf("Zombie process %d was killed\n", zombie);

    // parent process waits for the third and last signal, exiting the program
    pause();
//    printf("Last signal received, exiting program...\n");
    exit(0);
    
    return 0;
}