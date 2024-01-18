
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

void	set_fd(s_cmd *cmd)
{
	if (cmd->fd_in)
	{
		printf("cmd->fd_in = %d\n", cmd->fd_in);
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out)
	{
		printf("cmd->fd_out = %d\n", cmd->fd_out);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	child_process(t_gc *garbage, s_cmd *cmd)
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

	fd[0] = -1;
	fd[1] = -1;
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
	if (nb_cmd != 1)
		waitpid(pid_pipe, NULL, WNOHANG);
	else
		waitpid(pid_pipe, NULL, 0);
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}

int	ft_exec_pipe(t_gc *garbage, s_cmd *cmd, int *fdd, int nb_cmd)
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
	waitpid(-1, NULL, 0);
	return (0);
}

int	ft_exec(t_gc *garbage, s_cmd *cmd)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
		child_process(garbage, cmd);
	// g_signal = 1;
	is_builtins(garbage, cmd->line, 1);
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == 3)
		garbage->ret = 131;
	else if (WTERMSIG(status) == 2)
		garbage->ret = 130;
	else
		garbage->ret = WEXITSTATUS(status);
	// printf("WIFEXITED = %d\n", WIFEXITED(status));
	// printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
	// printf("WEFSIGNALED = %d\n", WIFSIGNALED(status));
	// printf("WTERMSIG = %d\n", WTERMSIG(status));
	// printf("WCOREDUMP = %d\n", __WCOREDUMP(status));
	// printf("WSTOPSIG = %d\n", WSTOPSIG(status));
	// printf("garbage->ret = %d\n", garbage->ret);
	return (0);
}

int	setup_exec(t_gc *garbage, s_cmd *cmd, int nb_cmd)
{
	int	fdd;

	fdd = dup(0);
	if (!garbage->line || !cmd)
		return (0);
	if (!garbage->pipe && !ft_strncmp("exit", cmd->line[0], ft_strlen(cmd->line[0])))
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
	// printf("cmd->fd_in = %d\n", cmd->fd_in);
	// printf("cmd->fd_out = %d\n", cmd->fd_out);
	// if (cmd->fd_in)
	// 	close(cmd->fd_in);
	// if (cmd->fd_out)
	// 	close(cmd->fd_out);
	return (0);
}