#include <sys/wait.h>
 #include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    pid_t pid = fork();

    if (pid  == 0)
    {
        static int cnt = 0;
        while(1)
        {
            cnt++;
            printf("child is running %d\r\n",  cnt);
            if (cnt >= 10)
            {
                cnt = 0;
                exit(0);
            }
            sleep(1);
        }
    }

    if (pid > 0)
    {
        int status;
        int f_cnt = 0;
        pid_t  child_pid;
        while (1)
        {
            child_pid =  waitpid(pid, &status, WNOHANG);      
            if (child_pid == 0)
            {
                printf("father is runing %d\r\n", ++f_cnt);
            }
            else if (child_pid == -1)
            {
                printf("waitpid error\r\n");
                break;
            }
            else
            {
                printf("child pid = %d, exit value = %d\r\n", child_pid, status); 
                break;
            }
            
            sleep(1);
        }
    }

    return 0;
}