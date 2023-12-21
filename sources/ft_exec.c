/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:09 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 18:28:06 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void    ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage)
{
    write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
    free_tab(paths);
    garbage->ret = 127;
    exit(1);
}

int check_sep_exec(t_arg *s_cmd)
{
    if (!s_cmd->sep)
        return (0);
    if (!ft_strncmp(s_cmd->sep, "<", 2))
        return (1);
    if (!ft_strncmp(s_cmd->sep, ">", 2))
        return (2);
    if (!ft_strncmp(s_cmd->sep, "<<", 3))
        return (3);
    if (!ft_strncmp(s_cmd->sep, ">>", 3))
        return (4);
    return (5);
}

int count_sep_exec(t_arg *s_cmd, char *sep1, char *sep2)
{
    int i;

    i = 0;
    while (s_cmd->next)
    {
        if (!ft_strncmp(s_cmd->sep, sep1, 3) || !ft_strncmp(s_cmd->sep, sep2, 3))
            i++;
        s_cmd = s_cmd->next;
    }
    return (i);
}

int ft_open(char *file, int typeofsep)
{
	printf("file = %s\n", file);
    if (typeofsep == 1)
    {
        if (access(file, F_OK) == -1)
            return (-1);
        if (access(file, R_OK) == -1)
            return (-1);
        return (open(file, O_RDONLY));
    }
    else if (typeofsep == 2)
    {
        if (access(file, F_OK) == -1)
            return (open(file, O_CREAT | O_RDWR, 0000644));
        else if (access(file, R_OK) == -1)
            return (-1);
        else if (access(file, W_OK) == -1)
            return (-1);
        return (open(file, O_TRUNC | O_RDWR, 0000644));
    }
    else if (typeofsep == 3)
    {
        printf("is heredoc\n");
        return (10);
    }
    else if (typeofsep == 4)
    {
        if (access(file, F_OK) == -1)
            return (open(file, O_APPEND | O_CREAT | O_RDWR, 0000644));
        else if (access(file, R_OK) == -1)
            return (-1);
        else if (access(file, W_OK) == -1)
            return (-1);
        return (open(file, O_APPEND | O_RDWR, 0000644));
    }
	return (-1);
}

void    ft_exec(t_arg *s_cmd, char **paths, t_gc *garbage, t_exec *ex)
{
	int 	pid;
	char	*cmd_path;
	char	buf[2];

    (void)buf;
    (void)ex;
	pid = fork();
	if (pid == -1)
		return ;
	if (!pid)
	{
		if (ex->infile && ex->infile[ex->i] > 0)
		{
			if (ex->r)
			{
				dup2(ex->infile[ex->i], ex->res_pipex);
				ex->r = 0;
			}
			else
				dup2(ex->infile[ex->i], STDIN_FILENO);
		}
    // printf("D\n");
    // printf("%s\n", s_cmd->line[0]);
		if (ex->outfile && ex->outfile[ex->o] > 0)
		{
			if (ex->r)
			{
				dup2(ex->outfile[ex->o], ex->res_pipex);
				ex->r = 0;
			}
			else
				dup2(ex->outfile[ex->o], STDOUT_FILENO);
        }
        if (is_builtins(garbage, s_cmd->line) == 2)
        {
            printf("exit\n");
			exit(0);
        }
        // printf("avant execve line[0] = %s sep = %s\n", s_cmd->line[0], s_cmd->sep);
        if (s_cmd->line[0][0] == ' ')
        {
            // printf("exit\n");   
            exit(0);
        }
		cmd_path = get_cmd(paths, s_cmd->line, garbage->blts->env);
		if (!cmd_path)
			ft_cmd_not_find(paths, s_cmd->line[0], garbage);
		execve(cmd_path, s_cmd->line, garbage->blts->env);
	}
}

int init_t_exec(t_exec *ex, t_arg *s_cmd, t_gc *garbage)
{
    ex->i = -1;
    ex->o = -1;
    ex->r = 0;
    ex->infile = NULL;
    ex->outfile = NULL;
    ex->paths = ft_split(find_path(garbage->blts->env), ':');
    ex->res_pipex = -1;
	if (count_sep_exec(s_cmd, "<", "<<"))
	{
    	ex->infile = malloc(sizeof(int) * count_sep_exec(s_cmd, "<", "<<"));
    		if (!ex->infile)
        		return (1);
		ex->infile[0] = -1;
	}
	if (count_sep_exec(s_cmd, ">", ">>"))
	{
    	ex->outfile = malloc(sizeof(int) * count_sep_exec(s_cmd, ">", ">>"));
    		if (!ex->outfile)
			{
				return (1);
			}
		ex->outfile[0] = -1;
	}
    return (0);
}

int init_open(t_exec *ex, t_arg *s_cmd, int typeofsep)
{
    if (typeofsep && typeofsep % 2 == 0)
    {
        printf("outfile open\n");
        ex->o++;
        ex->outfile[ex->o] = ft_open(s_cmd->next->line[0], typeofsep);
        if (ex->outfile[ex->o] == -1)
        {
            printf("error access file or open %s ", s_cmd->next->line[0]);
            return (1);
        }
        reset_line(s_cmd->next->line);
    }
    if (typeofsep && typeofsep % 2 == 1 && typeofsep != 5)
    {
        ex->i++;
        ex->infile[ex->i] = ft_open(s_cmd->next->line[0], typeofsep);
        if (ex->infile[ex->i] == -1)
        {
            printf("error access file or open %s\n", s_cmd->next->line[0]);
            return (1);
        }
        reset_line(s_cmd->next->line);
    }
    return (0);
}

char    *convert_tab_2_str(char **tabl)
{
    int i;
    char    *res;

    i = 1;
    if (!tabl[0])
        return (NULL);
    res = ft_strdup(tabl[0]);
    if (!res)
        return (NULL);
    while (tabl[i])
    {
		res = ft_strjoin_fs1(res, " ");
        res = ft_strjoin_fs1(res, tabl[i]);
        if (!res)
            return (NULL);
        i++;
    }
    return (res);
}

int count_pipex_cmds(t_arg *s_cmd)
{
    t_arg	*tmp;
    int		nb_cmd;

    tmp = s_cmd;
    nb_cmd = 1;
	while (tmp && !ft_strncmp(tmp->sep, "|", 2))
    {
        nb_cmd++;
        tmp = tmp->next;
    }
	return (nb_cmd);
}

int	init_pipex(t_exec *ex, t_arg *s_cmd, char **env)
{
    int     nb_cmd;
    char    **cmds_pipex;
    char    *str_cmd;
    int     i;

    // printf("init_pipex\n");
    i = 0;
	nb_cmd = count_pipex_cmds(s_cmd);
    ex->res_pipex = open(".res_pipex", O_CREAT | O_TRUNC | O_RDWR, 0000644);
    cmds_pipex = malloc(sizeof(char *) * (nb_cmd + 1));
    if (!cmds_pipex)
        return (-1);
    while (i < nb_cmd)
    {
        str_cmd = convert_tab_2_str(s_cmd->line);
        if (!str_cmd)
            return (-1);
        cmds_pipex[i] = str_cmd;
        i++;
		if (s_cmd->next)
    		s_cmd = s_cmd->next;
    }
    cmds_pipex[i] = NULL;
    // printf("avant pipex\n");
	pipex(nb_cmd, cmds_pipex, ex, env);
    // printf("apres pipex\n");
    dup2(STDOUT_FILENO, ex->res_pipex);
	return (nb_cmd);
}

void    ft_init_exec(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
    int typeofsep;
    int i;

    typeofsep = 0;
    // printf("A\n");
    typeofsep = check_sep_exec(s_cmd);
    if (init_open(ex, s_cmd, typeofsep))
        return ;
    if (typeofsep == 5)
	{
        i = init_pipex(ex, s_cmd, garbage->blts->env);
        if (i < 0)
            return ;
        // printf("AAAAAAAAAAAAAAAAAAAAAA\n");
        while (i-- && s_cmd->next)
        {
            s_cmd = s_cmd->next;
            garbage->nb_exec--;
        }
		ex->r = 1;
        // printf("BBBBBBBBBBBBBBBBBBb\n");
        if (!s_cmd->next)
            return ;
	}
    // printf("CCCCCCCCCCCCCCCCCCCCCCC\n");
	if (s_cmd->line[0])
        ft_exec(s_cmd, ex->paths, garbage, ex);
    // printf("DDDDDDDDDDDDDDDDDDDDD\n");
}
