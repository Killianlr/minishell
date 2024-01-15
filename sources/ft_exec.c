/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:09 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 14:48:45 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	set_fd(ex, garbage);
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

void	ft_exec(t_arg *s_cmd, char **paths, t_gc *garbage, t_exec *ex)
{
	int		pid;
	int		status;

	status = 0;
	if (ft_is_empty(s_cmd->line[0]))
		return ;
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		child_process(garbage, s_cmd, ex, paths);
	if (ex->idx == ex->nb_pipe)
	{
		close_pipes(ex);
		ex->p = 0;
	}
	if (ex->p == 1)
		return ;
	waitpid(pid, &status, 0);
	garbage->ret = status / 256;
	parent_process(garbage, s_cmd, ex);
	if (!s_cmd->next)
		close_files(ex);
}
