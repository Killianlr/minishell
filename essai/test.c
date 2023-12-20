
#include "essai.h"

//pip[0] == READ
//pip[1] == WRITE

int main(void)
{
    int fd;
    char    buf[4096];

    fd = open("file.txt", O_RDWR, 0000644);
    read(fd, buf, 4096);
    printf("%s\n", buf);
}