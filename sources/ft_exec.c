/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:09 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/03 16:44:45 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void    set_fd(t_exec *ex)
{
	char	buf[4096];

    if (ex->infile && ex->infile[ex->i] > 0)
	{
		if (ex->r)
		{
			dup2(ex->infile[ex->i], ex->res_pipex);
			ex->r = 0;
		}
		else
			dup2(ex->infile[ex->i], STDIN_FILENO);
	}
	if (ex->outfile && ex->outfile[ex->o] > 0)
	{
		if (ex->r)
		{
            read(ex->res_pipex, buf, 4096);
            write(ex->outfile[ex->o], buf, ft_strlen(buf));
			ex->r = 0;
		}
		else
			dup2(ex->outfile[ex->o], STDOUT_FILENO);
    }
}

void    parent_process(t_gc *garbage, t_arg *s_cmd)
{
    ft_export(garbage, s_cmd->line, 1);
    ft_define_var(garbage, s_cmd->line);
	ft_unset(garbage, s_cmd->line);
}

void    child_process(t_gc *garbage, t_arg *s_cmd, t_exec *ex, char **paths)
{
	char	*cmd_path;

    set_fd(ex);
    if (is_builtins(garbage, s_cmd->line) == 2)
		exit_child(garbage);
    if (s_cmd->line[0][0] == ' ')
    {
        exit_child(garbage);
    }
	cmd_path = get_cmd(paths, s_cmd->line, garbage->blts->env);
	if (!cmd_path)
    {
        ft_cmd_not_find(paths, s_cmd->line[0], garbage);
    }
	execve(cmd_path, s_cmd->line, garbage->blts->env);
}

void    ft_exec(t_arg *s_cmd, char **paths, t_gc *garbage, t_exec *ex)
{
	int 	pid;

    (void)ex;
	pid = fork();
	if (pid == -1)
		return ;
    if (pid > 0)
    {
        parent_process(garbage, s_cmd);
    }
	else
	{
        child_process(garbage, s_cmd, ex, paths);
	}
}
