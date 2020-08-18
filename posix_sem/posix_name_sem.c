#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
  #include <stdlib.h>

#define handler_err(err) \
                do{ perror(err); exit(0);} while(0)

#define SEM_NAME    "/name_sem"

int main(int argc ,char **argv)
{
    sem_t *name_sem = sem_open(SEM_NAME,  O_RDWR | O_CREAT,  S_IRWXU | S_IRWXG, 0);
    if (name_sem == SEM_FAILED)
    {
        handler_err("sem_open");
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        int ret;
        while (1)
        {
            ret = sem_wait(name_sem);
            if (ret == 0)
            {
                printf("child is running\r\n");
            }
        }
    }
    else
    {
        char buf[100];
        char *ret;
        while (1)
        {
            ret = fgets(buf, sizeof(buf), stdin);  
            if (ret != NULL)
            {
                printf("father : %s\r\n", buf);
            }
            if (strstr(buf, "post")  != NULL)
            {
                 sem_post(name_sem);      //释放信号量
            }    
        }
        sem_close(name_sem);
        sem_unlink(SEM_NAME);
    }
    
    return 0;
}