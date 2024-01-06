
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int ac, char **av, char **env)
{
    int status;
    int pid;
    char    **cmd;
    int     ret;
    int     val_exec;
    (void)ac;
    (void)av;

    cmd[0] = "./a.out";
    cmd[1] = NULL;
    pid = fork();
    if (!pid)
    {
        printf("int child\n");
        val_exec = execve("./a.out", cmd, env);
        printf("val_exec = %d\n", val_exec);
    }
    else
    {
        printf("in parent\n");
        waitpid(pid, &status, 0);
        ret = status / 256;
        printf("ret = %d\n", ret);
    }
    return (0);
}