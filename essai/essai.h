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

void    ft_exec(t_arg *s_cmd, char **env);

#endif