/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:19:59 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/21 13:53:47 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_fd(t_cmd *cmd)
{
	if (cmd->fd_in)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	wait_child_status(t_gc *garbage, int pid, int status)
{
	extern int	g_signal;

	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == 3)
	{
		write(1, "Quit (core dumped)\n", 20);
		garbage->ret = 131;
	}
	else if (WTERMSIG(status) == 2)
	{
		printf("\n");
		garbage->ret = 130;
	}
	else
	{
		garbage->ret = WEXITSTATUS(status);
		g_signal = garbage->ret;
	}
}

int	ft_lstsize_cmd(t_cmd *lst)
{
	t_cmd	*tmp;
	int		size;

	size = 0;
	if (!lst)
		return (0);
	tmp = lst->next;
	while (tmp)
	{
		lst = lst->next;
		tmp = lst;
		size++;
	}
	if (lst)
		size++;
	return (size);
}

void	rln2(char *pwd, DIR *directory)
{
	free(pwd);
	closedir(directory);
}

char	*rln(char *cmd, char *pwd, DIR *directory, struct dirent *entry)
{
	char	*path;

	while (1)
	{
		entry = readdir(directory);
		if (!entry)
			break ;
		if (!ft_strncmp(entry->d_name, cmd, ft_strlen(cmd)))
		{
			path = ft_strjoin(pwd, cmd);
			if (!path)
			{
				rln2(pwd, directory);
				return (NULL);
			}
			if (access(path, 0) == 0)
			{
				rln2(pwd, directory);
				return (path);
			}
			free(path);
		}
	}
	rln2(pwd, directory);
	return (NULL);
}
