/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:49:48 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/20 17:52:34 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*check_current_dir(char *cmd)
{
	DIR				*directory;
	struct dirent	*entry;
	char			*pwd;

	directory = opendir(".");
	if (!directory)
		return (NULL);
	pwd = ft_strjoin_fs1(get_pwd(), "/");
	if (!pwd)
	{
		closedir(directory);
		return (NULL);
	}
	entry = NULL;
	return (rln(cmd, pwd, directory, entry));
}

void	relativ_of_absolut(t_gc *garbage, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[0][i] && cmd[0][i] == '.' && cmd[0][i + 1] == '.'
		&& cmd[0][i + 2] == '/')
		i += 3;
	if (i)
	{
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, garbage->blts->env);
	}
	else if (cmd[0][i] == '/' || (cmd[0][i] == '.' && cmd[0][i + 1] == '/'))
	{
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, garbage->blts->env);
	}
}
