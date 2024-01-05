/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:55:48 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/05 18:29:45 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

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

void	get_pipes(t_p *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_nbr - 1)
	{
		if (pipe(pip->pipe + 2 * i) < 0)
			free_parent(pip);
		i++;
	}
}

int	pipex(int ac, char **av, t_exec *ex, char **envp)
{
	t_p	pip;

	if (ex->infile)
		pip.infile = ex->infile[ex->i];
	else
		pip.infile = open(".infile_tmp", O_CREAT | O_TRUNC | O_RDWR, 0000644);
	if (!pip.infile)
		msg_error_2("error pipex\n", &pip);
	pip.outfile = ex->res_pipex;
	pip.cmd_nbr = ac;
	pip.pipe_nbr = 2 * (pip.cmd_nbr - 1);
	pip.pipe = malloc(sizeof(int) * pip.pipe_nbr);
	if (!pip.pipe)
		msg_error("error pipe\n", &pip, ex);
	pip.path = ft_split(find_path(envp), ':');
	if (!pip.path)
		free_pipe(&pip, ex);
	get_pipes(&pip);
	pip.idx = -1;
	while (++(pip.idx) < pip.cmd_nbr)
		child(pip, av, envp);
	close_pipes(&pip);
	free_main(&pip, ex, av);
	waitpid(-1, NULL, 0);
	return (0);
}

int	init_pipex(t_exec *ex, t_arg *s_cmd, char **env)
{
    int     nb_cmd;
    char    **cmds_pipex;
    char    *str_cmd;
    int     i;

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
    pipex(nb_cmd, cmds_pipex, ex, env);
	return (nb_cmd);
}
