#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>         
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


int main(int argc, char **argv)
{
    char write_buf[] = "Linux,RT-Thread,uCos,FreeRTOS";
    char read_buf[1024]; 

    int len = strlen(write_buf);

    if (access("test_fifo", F_OK))                       //判断管道文件是否存在
    {
        int ret = mkfifo("test_fifo", 0644);              //创建管道
         if (ret < 0)
         {
             printf("fail to mkfifo\r\n");
            return -1;
        }
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("failed to fork\r\n");
        return -1;
    }

    if (pid == 0)      //子进程   
    {
        int fifo = open("test_fifo",  O_WRONLY);          //打开管道
        write(fifo, write_buf, strlen(write_buf));         
        close(fifo);
    }

    if (pid > 0)     //父进程  
    {
        int fifo = open("test_fifo", O_RDONLY);        //父进程打开管道
        read(fifo, read_buf, len);                       //从管道中读取数据     
        printf("read : %s\r\n", read_buf);
        close(fifo);
    }

    return 0;
}