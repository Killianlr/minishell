/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/18 16:19:41 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_fd(s_cmd *cmd)
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

static void child_pipe(t_gc *garbage, s_cmd *cmd, int fd[2], int *fdd)
{
	char	**paths;
	char	*cmd_path;

	close(fd[0]);
	close(0);
	dup(*fdd);
	close(*fdd);
	if (cmd->next)
	{
		close(1);
		dup(fd[1]);
		close(fd[1]);
	}
	set_fd(cmd);
	if (is_builtins(garbage, cmd->line, 0) == 2)
		exit_child(garbage, 0);
	paths = ft_split(find_path(garbage->blts->env), ':');
	cmd_path = get_cmd(paths, cmd->line, garbage);
	if (!cmd_path)
	{
		free_tab(paths);
		write(2, cmd->line[0], ft_strlen(cmd->line[0]));
		write(2, ": command not found\n", 21);
		exit_free(garbage, 127);
	}
	execve(cmd_path, cmd->line, garbage->blts->env);
}

int	run_pipe(t_gc *garbage, s_cmd *cmd, int fdd, int nb_cmd)
{
	int	fd[2];
	int	pid_pipe;
	int	status;
	extern int g_signal;

	fd[0] = -1;
	fd[1] = -1;
	status = 0;
	if (pipe(fd) < 0)
		return (-1);
	pid_pipe = fork();
	if (pid_pipe < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(fdd);
		return (-1);
	}
	else if (!pid_pipe)
	{
		child_pipe(garbage, cmd, fd, &fdd);
	}
	g_signal = 1;
	if (nb_cmd == 1)
	{
		waitpid(pid_pipe, &status, 0);
		if (WTERMSIG(status) == 3)
			garbage->ret = 131;
		else if (WTERMSIG(status) == 2)
			garbage->ret = 130;
		else
			garbage->ret = WEXITSTATUS(status);
	}
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}

int	ft_lstsize_cmd(s_cmd *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
