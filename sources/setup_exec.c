/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:36:56 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/20 12:24:05 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **paths, char	**cmd, t_gc *garbage)
{
	char	*tmp;
	char	*command;

	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, garbage->blts->env);
	}
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

void	child_process(t_gc *garbage, t_cmd *cmd)
{
	char	**paths;
	char	*cmd_path;

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

int	ft_exec_pipe(t_gc *garbage, t_cmd *cmd, int *fdd, int nb_cmd)
{
	while (cmd)
	{
		*fdd = run_pipe(garbage, cmd, *fdd, nb_cmd);
		if (cmd->fd_in)
			close(cmd->fd_in);
		if (cmd->fd_out)
			close(cmd->fd_out);
		cmd = cmd->next;
		nb_cmd--;
	}
	while (wait(NULL) != -1)
		wait(NULL);
	return (0);
}

int	ft_exec(t_gc *garbage, t_cmd *cmd)
{
	int			pid;
	int			status;
	extern int	g_signal;

	status = 0;
	signal(SIGQUIT, signal_handler_exec);
	signal(SIGINT, signal_handler_exec);
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
		child_process(garbage, cmd);
	g_signal = 1;
	is_builtins(garbage, cmd->line, 1);
	wait_child_status(garbage, pid, status);
	return (0);
}

int	setup_exec(t_gc *garbage, t_cmd *cmd, int nb_cmd)
{
	int	fdd;

	if (!garbage->line || !cmd)
		return (0);
	fdd = dup(0);
	if (!garbage->pipe
		&& !ft_strncmp("exit", cmd->line[0], ft_strlen(cmd->line[0])))
	{
		close(fdd);
		ft_exit(garbage, cmd->line);
	}
	if (garbage->pipe)
		ft_exec_pipe(garbage, cmd, &fdd, nb_cmd);
	else
	{
		close(fdd);
		ft_exec(garbage, cmd);
	}
	close(fdd);
	return (0);
}
