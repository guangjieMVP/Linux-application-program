#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


char buf[] = "I Love Linux";

int main(int argc, char **argv)
{

    char * p = mmap(NULL, 40, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //MAP_ANONYMOUS 匿名映射

    if (p != MAP_FAILED)
    {
        strncpy(p, buf, sizeof(buf));
    }
    else
    {
        perror("mmap");
        exit(0);
    }
    printf("mmap mem : %s\r\n", p);

   int ret =  munmap(p, 40);
    if (ret < 0)
    {
        perror("munmap");
    }
    
    return 0;
}