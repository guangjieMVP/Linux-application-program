#include <unistd.h>
#include <stdio.h>
#include <string.h>
 #include <signal.h>
 #include <time.h>
 #include <errno.h>
 #include <stdlib.h>

void  signal_int_handler(int signum)
{
    printf("Hello!!!  Linux\r\n");
}

int main(int argc, char **argv)
{
    struct timespec req, rem;
    int ret;

    signal(SIGINT, signal_int_handler);

    req.tv_sec    = 2;
    req.tv_nsec  = 100;

    for(;;)
    {
        printf("hello world\r\n");

        ret = nanosleep(&req, &rem); 
        if(ret == -1 && errno != EINTR)
        {
            printf("exit\r\n");
            exit(0);
        }

        if(ret == 0)
        {
            req.tv_sec    = 2;
            req.tv_nsec  = 100;
        }
   //     printf("remain %ld sec %ld nsec", rem.tv_sec, rem.tv_nsec);
  //      req = rem;
    }
    return 0;
}