#ifndef ESSAI_H
# define ESSAI_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>

typedef struct arg
{
    char    **line;
    char    *sep;
    int     h_doc;
    struct arg  *next;
}               t_arg;

typedef struct exec
{
    int *infile;
    int i;
    int *outfile;
    int o;
    char **paths;
    int res_pipex;
    int r;
}           t_exec;

void    ft_init_exec(t_arg *s_cmd, char **env, int lstsize);
char	*find_path(char **envp);
char	*get_cmd(char **paths, char	**cmd, char **envp);
int	    pipex(int ac, char **av, t_exec *ex, char **envp);

#endif