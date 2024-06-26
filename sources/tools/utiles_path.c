/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:49:48 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/23 14:18:48 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_max_int_tab(char **env)
{
	int		r;

	r = 0;
	while (env[r])
		r++;
	return (r);
}

static char	*find_path_2(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_path(char **envp)
{
	int	r;
	int	max;

	r = 0;
	max = find_max_int_tab(envp);
	while (r < max && ft_strncmp("PATH", envp[r], 4))
		r++;
	if (r == max)
	{
		return (NULL);
	}
	else
		return (find_path_2(envp));
	return (NULL);
}

void	relativ_of_absolut(t_gc *garbage, char **cmd, char **paths)
{
	int	i;

	i = 0;
	while (cmd[0][i] && cmd[0][i] == '.' && cmd[0][i + 1] == '.'
		&& cmd[0][i + 2] == '/')
		i += 3;
	if (i)
	{	
		if (isdirectory(cmd[0]))
			exit_is_dir(paths, cmd, garbage);
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, garbage->blts->env);
	}
	else if (cmd[0][i] == '/' || (cmd[0][i] == '.' && cmd[0][i + 1] == '/'))
	{
		if (isdirectory(cmd[0]))
			exit_is_dir(paths, cmd, garbage);
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, garbage->blts->env);
	}
}
