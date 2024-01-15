/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:35 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 10:45:53 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_lstsize_targ(t_arg *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	reset_line(char **tabl, t_gc *garbage)
{
	int		i;
	char	*save;

	if (!tabl[1])
		garbage->go = 0;
	i = 0;
	save = tabl[0];
	if (ft_strlen_tab(tabl) <= 1)
		return ;
	while (tabl[i])
	{
		tabl[i] = tabl[i + 1];
		i++;
	}
	free(save);
	tabl[i] = NULL;
}

int	count_sep_exec(t_arg *s_cmd, char *sep1, char *sep2)
{
	int	i;

	i = 0;
	while (s_cmd->next)
	{
		if (!ft_strncmp(s_cmd->sep, sep1, 3)
			|| !ft_strncmp(s_cmd->sep, sep2, 3))
			i++;
		s_cmd = s_cmd->next;
	}
	return (i);
}

void	put_respipex(t_exec *ex)
{
	char	*bufrun;
	char	*bufret;
	int		res_pipex;

	res_pipex = open(".res_pipex", O_RDONLY);
	if (!res_pipex)
		return ;
	bufrun = get_next_line(res_pipex, 0);
	bufret = NULL;
	while (1)
	{
		bufret = ft_strjoin_fs2(bufret, bufrun);
		if (!bufret)
			return ;
		bufrun = get_next_line(res_pipex, 0);
		if (!bufrun)
			break ;
	}
	write(1, bufret, ft_strlen(bufret));
	free(bufret);
	close(res_pipex);
	if (ex->infile || ex->outfile)
		close_files(ex);
	unlink(".res_pipex");
}

char	*get_cmd(char **paths, char	**cmd, t_gc *garbage, t_exec *ex)
{
	char	*tmp;
	char	*command;

	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, garbage->blts->env);
	}
	else if (is_builtins(garbage, cmd) == 2)
		exit_child(garbage, ex);
	if (!paths)
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}
