/***************************************************************************************************
  * @file:     xxx.c
  * @author:   guangjieMVP
  * @github:   https://github.com/guangjieMVP
  * @version:  v1.0.0
  * @date:     2020-xx-xx
  * @brief:               
*****************************************************************************************************/
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int retval = 0xff;
void *thread1_entry(void *arg)
{
    static int cnt = 0;
    
    while (1)
    {
        printf("Linux %d\r\n", cnt++);
        if(cnt >= 10)
        {
            cnt = 0;
            pthread_exit(&retval);
        }
        sleep(2);
    }
}

void *thread2_entry(void *arg)
{
    while (1)
    {
        printf("ubuntu\r\n");
        sleep(3);
    }
}

int main(int argc, char **argv)
{
    pthread_t thread1;
    pthread_t thread2;
    int ret;
    pthread_attr_t attr;
    
    ret = pthread_attr_init(&attr);
    if(ret != 0)
    {
        printf("faild to init attr\r\n");
        exit(0);
    }
    
    ret = pthread_attr_setdetachstate(attr, PTHREAD_CREATE_DETACHED);
    if(ret != 0)
    {
        printf("faild to setdetach\r\n");
        exit(0);
    }
  
    pthread_create(&thread1, &attr, thread1_entry, NULL);
    pthread_create(&thread2, &attr, thread2_entry, NULL);
   
    
    static int maincnt = 0;
    unsigned char flag = 0;
    while(1)
    {
        printf("main thread %d\r\n", maincnt++);
        if(maincnt >= 10 && !flag)
        {
            maincnt = 0;
            flag = 1;
            pthread_cancel(thread2);
        }
        sleep(1);
    }
    
    return 0;
}