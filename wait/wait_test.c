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
        pid_t  child_pid;
    
        child_pid =  wait(&status);      //一直阻塞直到子进程退出
        printf("child pid = %d, exit value = %d\r\n", child_pid, status); 
    }

    return 0;
}