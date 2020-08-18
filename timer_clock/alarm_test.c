#include <unistd.h>
#include <stdio.h>
#include <string.h>
 #include <signal.h>

void  signal_alrm_handler(int signum)
{
    printf("Hello!!!  Linux\r\n");
}

int main(int argc, char **argv)
{
    signal(SIGALRM, signal_alrm_handler);

    alarm(10);

    pause();

    return 0;
}
