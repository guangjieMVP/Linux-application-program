#ifndef _COMMON_H_
#define _COMMON_H_

#define MSG_PATHNAME     "."
#define MSG_PRJID        1314

#define MSGBUF_SIZE      1024        //消息队列消息缓冲区大小
#define MSG_TYPE         1

/* 消息结构体 */
struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[MSGBUF_SIZE];    /* message data */
};

#endif