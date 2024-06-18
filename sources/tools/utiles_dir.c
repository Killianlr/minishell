/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:07:27 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/23 12:10:59 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	isdirectory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) < 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	exit_is_dir(char **paths, char **cmd, t_gc *garbage)
{
	free_tab(paths);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, " is a directory\n", 16);
	exit_free(garbage, 126);
}

void	ret_exit_dir(char *command, char **paths, char **cmd, t_gc *garbage)
{
	free(command);
	free_tab(paths);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, " is a directory\n", 16);
	exit_free(garbage, 126);
}
