/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:09 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 10:42:35 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipes(t_exec *ex)
{
	int	i;

	i = 0;
	while (i < (2 * ex->nb_pipe))
	{
		close(ex->pipex[i]);
		i++;
	}
}

void	set_fd(t_exec *ex)
{
	if (ex->p)
	{
		if (ex->idx == 0)
		{
			if (ex->infile && ex->infile[ex->i] > 0)
			{
				dup2(ex->infile[ex->i], STDIN_FILENO);
			}
			dup2(ex->pipex[1], STDOUT_FILENO);
		}
		else if (ex->idx == ex->nb_pipe)
		{
			if (ex->outfile && ex->outfile[ex->o] > 0)
			{
				dup2(ex->outfile[ex->o], STDOUT_FILENO);
			}
			dup2(ex->pipex[2 * ex->idx - 2], STDIN_FILENO);
		}
		else
		{
			dup2(ex->pipex[2 * ex->idx - 2], STDIN_FILENO);
			dup2(ex->pipex[2 * ex->idx + 1], STDOUT_FILENO);
		}
		close_pipes(ex);
		return ;
	}
	if (ex->infile && ex->infile[ex->i] > 0)
	{
		dup2(ex->infile[ex->i], STDIN_FILENO);
	}
	if (ex->outfile && ex->outfile[ex->o] > 0)
	{
		dup2(ex->outfile[ex->o], STDOUT_FILENO);
	}
}

void	parent_process(t_gc *garbage, t_arg *s_cmd, t_exec *ex)
{
	(void) ex;
	ft_export(garbage, s_cmd->line, 1);
	ft_define_var(garbage, s_cmd->line);
	ft_unset(garbage, s_cmd->line, 1);
	ft_cd_2(garbage, s_cmd->line);
	ft_echo_2(garbage, s_cmd->line);
}

void	child_process(t_gc *garbage, t_arg *s_cmd, t_exec *ex, char **paths)
{
	char	*cmd_path;

	if (s_cmd->line[0][0] == ' ')
	{
		exit_child(garbage, ex);
	}
	set_fd(ex);
	if (is_builtins(garbage, s_cmd->line) == 2)
	{
		exit_child(garbage, ex);
	}
	cmd_path = get_cmd(paths, s_cmd->line, garbage, ex);
	if (!cmd_path)
	{
		ft_cmd_not_find(paths, s_cmd->line[0], garbage, ex);
	}
	if (ex->infile || ex->outfile)
		close_files(ex);
	execve(cmd_path, s_cmd->line, garbage->blts->env);
}

void	close_files(t_exec *ex)
{
	int	i;
	int	o;

	i = ex->i;
	o = ex->o;
	if (ex->infile)
	{
		while (i >= 0)
		{
			close(ex->infile[i]);
			i--;
		}
	}
	if (ex->outfile)
	{
		while (o >= 0)
		{
			close(ex->outfile[o]);
			o--;
		}
	}
}

void	ft_exec(t_arg *s_cmd, char **paths, t_gc *garbage, t_exec *ex)
{
	int		pid;
	int		status;

	status = 0;
	if (ft_is_empty(s_cmd->line[0]))
	{
		return ;
	}
	pid = fork();
	if (pid == -1)
		return ;
	if (pid > 0)
	{
		// printf("commande pour exec = %s, ex->p = %d ex->idx = %d\n", s_cmd->line[0], ex->p, ex->idx);
		// printf("fin du parent de exec %s, ex->p = %d\n", s_cmd->line[0], ex->p);
		if (ex->idx == ex->nb_pipe)
		{
			// printf("close pipes\n");
			close_pipes(ex);
			ex->p = 0;
		}
		if (ex->p == 1)
			return ;
		waitpid(pid, &status, 0);
		garbage->ret = status / 256;
		parent_process(garbage, s_cmd, ex);
		if (!s_cmd->next)
		{
			close_files(ex);
		}
	}
	else
	{
		child_process(garbage, s_cmd, ex, paths);
	}
}
