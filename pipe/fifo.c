#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int fd;
char buf[1024];

int main(){

    mkfifo("fifo", )

    fd = open("fifo", O_RDONLY);

    read(fd, buf, 1024);


    return 0;
}