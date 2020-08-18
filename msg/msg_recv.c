#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

int main(int argc, char **argv)
{
    key_t key = ftok(MSG_PATHNAME, MSG_PRJID);    //创建消息队列的key
    int msgid = msgget(key, 0666 | IPC_CREAT);    //获取消息队列的id
    if(msgid < 0)
    {
        printf("failed to get msgid\r\n");
        return -1;
    }

    struct msgbuf my_msgbuf;
    my_msgbuf.mtype = MSG_TYPE;                //消息类型标识符
    memset(my_msgbuf.mtext, 0, MSGBUF_SIZE);   //清空消息缓冲区

    while(1)
    {
        msgrcv(msgid, &my_msgbuf, sizeof(my_msgbuf), MSG_TYPE, 0);
        printf("%s", my_msgbuf.mtext);
        // sleep(1);
    }

    return 0;
}



