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
    int fd = open("mmap_test.txt" , O_RDWR | O_CREAT,  S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("open");
        exit(0);
    }

    write(fd, buf, sizeof(buf));    
    
    struct stat filestat;
    int ret = fstat(fd, &filestat);
    if (ret < 0)
    {
        perror("fstat");
        exit(0);
    }

    char * p = mmap(NULL, filestat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (p != MAP_FAILED)
    {
        printf("map memory： %s\r\n", p);
    }
    else
    {
        perror("mmap");
        exit(0);
    }

   ret =  munmap(p, filestat.st_size);
    if (ret < 0)
    {
        perror("munmap");
    }
    
    return 0;
}