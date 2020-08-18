#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "common.h"

int main(int argc, char **argv)
{
    key_t key = ftok(SHM_PATHNAME, SHM_PRJID);             //创建key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);   // 获得shmid

    char *pbuf = (char *)shmat(shmid, NULL, 0);
    memset(pbuf, 0, SHM_SIZE);  

    char cnt = 0;
    while(1)
    {
        printf(pbuf, "linux message :", cnt++);
        sleep(1);
    }

    shmdt(pbuf);        //解除映射
    return 0;
}