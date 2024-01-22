/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/22 19:44:28 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_fd_pipe(int fd)
{
	close(1);
	dup(fd);
	close(fd);
}

void	child_pipe(t_gc *garbage, t_cmd *cmd, int fd[2], int *fdd)
{
	char	**paths;
	char	*cmd_path;

	close(fd[0]);
	close(0);
	dup(*fdd);
	close(*fdd);
	if (cmd->next)
		set_fd_pipe(fd[1]);
	set_fd(cmd);
	if (is_builtins(garbage, cmd->line, 0) == 2)
	{
		close(fd[1]);
		exit_child(garbage, 0);
	}	
	paths = ft_split(find_path(garbage->blts->env), ':');
	cmd_path = get_cmd(paths, cmd->line, garbage);
	if (!cmd_path)
	{
		close(fd[1]);
		free_tab(paths);
		write(2, cmd->line[0], ft_strlen(cmd->line[0]));
		write(2, ": command not found\n", 21);
		exit_free(garbage, 127);
	}
	execve(cmd_path, cmd->line, garbage->blts->env);
}

void	fck_norm(int fd[2], int fdd)
{
	close(fd[0]);
	close(fd[1]);
	close(fdd);
}

int	run_pipe(t_gc *garbage, t_cmd *cmd, int fdd, int nb_cmd)
{
	int			fd[2];
	int			pid_pipe;
	int			status;

	fd[0] = -1;
	fd[1] = -1;
	status = 0;
	if (pipe(fd) < 0)
		return (-1);
	pid_pipe = fork();
	if (pid_pipe < 0)
	{
		fck_norm(fd, fdd);
		return (-1);
	}
	else if (!pid_pipe)
		child_pipe(garbage, cmd, fd, &fdd);
	if (nb_cmd == 1)
		wait_child_status(garbage, pid_pipe, status);
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}
