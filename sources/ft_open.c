
#include "../includes/minishell.h"

int open_infile(char *file)
{
    int fd;

    if (access(file, F_OK) == -1)
        return (-1);
    if (access(file, R_OK) == -1)
        return (-1);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        printf("echec open file : %s\n", file);
    return (fd);
}

int open_outfile_otrunc(char *file)
{
    int fd;

    if (access(file, F_OK) == -1)
        return (open(file, O_CREAT | O_RDWR, 0000644));
    else if (access(file, R_OK) == -1)
        return (-1);
    else if (access(file, W_OK) == -1)
        return (-1);
    fd = open(file, O_TRUNC | O_RDWR, 0000644);
    if (fd < 0)
        printf("echec open file : %s\n", file);
    return (fd);
}

int open_outfile_append(char *file)
{
    int fd;

    if (access(file, F_OK) == -1)
        return (open(file, O_APPEND | O_CREAT | O_RDWR, 0000644));
    else if (access(file, R_OK) == -1)
        return (-1);
    else if (access(file, W_OK) == -1)
        return (-1);
    fd = open(file, O_APPEND | O_RDWR, 0000644);
    if (fd < 0)
        printf("echec open file : %s\n", file);
    return (fd);
}

int ft_open(char *file, int typeofsep)
{
    int fd;
    
    if (typeofsep == 1)
    {
        fd = open_infile(file);
        return (fd);
    }
    else if (typeofsep == 2)
    {
        fd = open_outfile_otrunc(file);
        return (fd);
    }
    else if (typeofsep == 3)
    {
        fd = open(".heredoc_tmp", O_RDONLY);
        return (fd);
    }
    else if (typeofsep == 4)
    {
        fd = open_outfile_append(file);
        return (fd);
    }
	return (-1);
}