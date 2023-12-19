
#include "essai.h"

//pip[0] == READ
//pip[1] == WRITE

int main(void)
{
    int fd_res;
    int pip[2];

    fd_res = open("file.txt", O_APPEND, O_RDWR, 0000644);
    if (pipe(pip) < 0)
        return (-1);
    close(pip[0]);
    dup2(pip[1], STDOUT_FILENO);
    printf("hello world !\n");
    close(pip[1]);
    dup2(fd_res, pip[0]);
    close(pip[0]);
    close(fd_res);
    return (0);
}