#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

int main()
{
    // gettimeofday() saves the current time in a timeval struct
    struct timeval start, end;
    char path[256] = "";
    char arg[256] = "";
    double command_time = 0, total_time = 0;
    int result;
    pid_t child;

    while (scanf("%s %s", path, arg) != EOF)
    {
        // the second param, to get the time zone, is obsolete, so we pass NULL
        gettimeofday(&start, NULL);
        fflush(stdout);

        // the thing is, we are basically sacrificing a child process to do the work for us, because the programs is ending after the execl, so the child is used for getting the errors and the parent only gets the exit status and continues the loop
        child = fork();
        
        // the child process is the one executing the command
        if(child == 0)
        {
            // let the child deal with this shit
            // tried with system(), does not work
            // execl changes errno state
            execl(path, path, arg, NULL);

            // execution past execl only continues if smth went wrong, so we print the respective error message
            if (strcmp(strerror(errno), "Success") != 0){
                printf("> Erro: %s\n", strerror(errno));
            }
            fclose(stdin);
            exit(errno);
        }
        else
        {
            // the thing is, the parent process is just going ahead and executing the rest of the program, but we actually need it to wait for its child exit status
            waitpid(child, &result, 0);
            fflush(stdout);
            
            // gets the exit status returned by the child
            result = WEXITSTATUS(result);

            gettimeofday(&end, NULL);
            fflush(stdout);
            
            // seconds + (microseconds -> seconds. ps: one second is 1000000 microseconds)
            command_time = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec) / 1000000.0);
                    
            printf("> Demorou %.1lf segundos, retornou %d\n", command_time, result);
            
            total_time += command_time;
        }
    }

    printf(">> O tempo total foi de %.1lf segundos\n", total_time);

    return 0;
}