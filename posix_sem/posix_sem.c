#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

#define handler_err(err) \
                do{ perror(err); } while(0)

int main(int argc ,char **argv)
{
    sem_t  *p_sem = (sem_t *)mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //MAP_ANONYMOUS 匿名映射
   if (p_sem != MAP_FAILED)
    {
        printf("sem addr ： %p\r\n", p_sem);
    }
    else
    {
        perror("mmap");
        exit(0);
    }

    if (sem_init(p_sem ,  2, 0) < 0)  //初始化无名信号量
    {
        handler_err("sem_open");
        exit(0);
    }

    pid_t pid = fork();
    if (pid == 0)
    {
        int ret;
        int sem_val;
        int cnt = 0;
        while (1)
        {
            ret = sem_wait(p_sem);
            if (ret == 0)
            {
                printf("child is running\r\n");
            }
            else
            {
                perror("sem_wait");
            }
            sem_getvalue(p_sem, &sem_val);
            printf("sem val : %d\r\n", sem_val);
            printf("cnt : %d\r\n", cnt++);
        }
    }
    else
    {
        char buf[100];
        char *ret;
        int sem_val;
        while (1)
        {
            ret = fgets(buf, sizeof(buf), stdin);  
            if (ret != NULL)
            {
                // printf("father : %s\r\n", buf);
            }
            if (strstr(buf, "post")  != NULL)
            {
                 if (sem_post(p_sem) < 0);      //释放信号量
                 {
                    perror("sem_post");
                 }
                sem_getvalue(p_sem, &sem_val);
                printf("sem val : %d\r\n", sem_val);
            }    
        }
       
    }

    sem_close(p_sem);
    sem_destroy(p_sem);

    return 0;
}