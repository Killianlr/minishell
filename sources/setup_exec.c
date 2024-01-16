
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

void	child_process(t_gc *garbage, char **cmd)
{
	char	**paths;
	char	*cmd_path;
	int		ret_blts;

	ret_blts = is_builtins(garbage, cmd, 0);
	if (ret_blts == 1)
		exit_child(garbage, 1);
	else if (ret_blts == 2)
		exit_child(garbage, 0);
	paths = ft_split(find_path(garbage->blts->env), ':');
	cmd_path = get_cmd(paths, cmd, garbage);
	if (!cmd_path)
	{
		free_tab(paths);
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 21);
		exit_free(garbage, 127);
	}
	execve(cmd_path, cmd, garbage->blts->env);
}

int	ft_exec(t_gc *garbage, char **cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		child_process(garbage, cmd);
	}
	g_signal = 1;
	is_builtins(garbage, cmd, 1);
	waitpid(pid, &status, 0);
	if (WTERMSIG(status) == 2)
		status = 130;
	printf("status = %d\n", status);
	garbage->ret = status;
	printf("WIFEXITED = %d\n", WIFEXITED(status));
	printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
	printf("WEFSIGNALED = %d\n", WIFSIGNALED(status));
	printf("WTERMSIG = %d\n", WTERMSIG(status));
	printf("WCOREDUMP = %d\n", __WCOREDUMP(status));
	printf("WSTOPSIG = %d\n", WSTOPSIG(status));
	// printf("garbage->ret = %d\n", garbage->ret);
	return (0);
}

int	setup_exec(t_gc *garbage, char **cmd)
{
	if (!garbage->line)
		return (0);
	if (!ft_strncmp("exit", cmd[0], ft_strlen(cmd[0])))
		ft_exit(garbage, cmd);
	ft_exec(garbage, cmd);
	return (0);
}