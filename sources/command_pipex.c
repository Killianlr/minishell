/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:56:31 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 18:12:58 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	set_fd(int in, int out)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

char	*get_cmd(char **paths, char	**cmd, char **envp)
{
	char	*tmp;
	char	*command;

	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
	{
		if (access(cmd[0], 0) == 0)
			execve(cmd[0], cmd, envp);
	}
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

void	next(t_p pip, char **av, char **envp)
{
	close_pipes(&pip);
	pip.args = ft_split(av[pip.idx], ' ');
	pip.cmd = get_cmd(pip.path, pip.args, envp);
	if (!pip.cmd)
	{
		write(2, "command not found: ", 20);
		write(2, pip.args[0], ft_strlen(pip.args[0]));
		write(2, "\n", 1);
		free_child(&pip);
		exit(1);
	}
	execve(pip.cmd, pip.args, envp);
}

void	child(t_p pip, char **av, char **envp)
{
	pip.pid = fork();
	if (!pip.pid)
	{
		if (pip.idx == 0)
		{
			set_fd(pip.infile, pip.pipe[1]);
			close(pip.outfile);
		}
		else if (pip.idx == pip.cmd_nbr - 1)
		{
			set_fd(pip.pipe[2 * pip.idx - 2], pip.outfile);
			close(pip.infile);
		}
		else
		{
			set_fd(pip.pipe[2 * pip.idx - 2], pip.pipe[2 * pip.idx + 1]);
			close(pip.infile);
			close(pip.outfile);
		}
		next(pip, av, envp);
	}	
}
