#include <sys/wait.h>
 #include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

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
        siginfo_t info;
        memset(&info, 0, sizeof(siginfo_t));
        int f_cnt = 0;
        int ret;
        while (1)
        {
            if (ret =  waitid(P_PGID,  getpgid(getpid()), &info,  WEXITED | WNOHANG)  == -1)  //执行失败
            {
                perror("waitid\r\n");
                break;
            }
            else if (ret == 0)     //执行成功
            {
                 if (info.si_pid == 0) //没有子进程状态发生改变
                 {
                    printf("no children changed state %d\r\n", f_cnt++);
                 }
                 else
                 {
                     printf("child pid = %d status = %d\r\n",  pid, info.si_status );
                 }
            }
            sleep(1);
        }
    }

    return 0;
}