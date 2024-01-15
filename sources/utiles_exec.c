/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:35 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 14:19:16 by kle-rest         ###   ########.fr       */
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
	{
		garbage->go = 0;
		garbage->rl = 1;
	}
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
