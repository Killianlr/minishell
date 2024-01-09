/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:09 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/08 15:39:31 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void    put_respipex(t_exec *ex)
{
    char    *bufrun;
    char    *bufret;
    int     res_pipex;

    res_pipex = open(".res_pipex", O_RDONLY);
    if (!res_pipex)
        return ;
    bufrun = get_next_line(res_pipex, 0);
    bufret = NULL;
    while (1)
    {
        bufret = ft_strjoin_fs2(bufret, bufrun);
        if (!bufret)
            return ;
        bufrun = get_next_line(res_pipex, 0);
        if (!bufrun)
            break ;
    }
    write(1, bufret, ft_strlen(bufret));
    free(bufret);
    close(res_pipex);
    if (ex->infile || ex->outfile)
        close_files(ex);
    unlink(".res_pipex");
}

void    set_fd(t_exec *ex)
{
    if (ex->infile && ex->infile[ex->i] > 0)
	{
		if (ex->r)
		{
			dup2(ex->infile[ex->i], ex->res_pipex);
            close(ex->res_pipex);
		}
		else
        {
			dup2(ex->infile[ex->i], STDIN_FILENO);
        }
	}
	if (ex->outfile && ex->outfile[ex->o] > 0)
	{
	    dup2(ex->outfile[ex->o], STDOUT_FILENO);
    }
}

void    parent_process(t_gc *garbage, t_arg *s_cmd, t_exec *ex)
{
    (void) ex;
    ft_export(garbage, s_cmd->line, 1);
    ft_define_var(garbage, s_cmd->line);
	ft_unset(garbage, s_cmd->line);
    ft_cd_2(garbage, s_cmd->line);
    ft_echo_2(garbage, s_cmd->line);
}

void    child_process(t_gc *garbage, t_arg *s_cmd, t_exec *ex, char **paths)
{
	char	*cmd_path;

    if (s_cmd->line[0][0] == ' ')
    {
        exit_child(garbage, ex);
    }
    set_fd(ex);
    if (is_builtins(garbage, s_cmd->line) == 2)
		exit_child(garbage, ex);
	cmd_path = get_cmd(paths, s_cmd->line, garbage, ex);
	if (!cmd_path)
    {
        ft_cmd_not_find(paths, s_cmd->line[0], garbage, ex);
    }
    if (ex->infile || ex->outfile)
            close_files(ex);
	execve(cmd_path, s_cmd->line, garbage->blts->env);
}

void    close_files(t_exec *ex)
{
    int i;
    int o;

    i = ex->i;
    o = ex->o;
    if (ex->infile)
    {
        while(i >= 0)
        {
            close(ex->infile[i]);
            i--;
        }
    }
    if (ex->outfile)
    {
        while(o >= 0)
        {
            close(ex->outfile[o]);
            o--;
        }
    }
}

void    ft_exec(t_arg *s_cmd, char **paths, t_gc *garbage, t_exec *ex)
{
	int 	pid;
    int     status;

    if (ft_is_empty(s_cmd->line[0]) && !s_cmd->sep)
    {
        return ;
    }
	pid = fork();
	if (pid == -1)
		return ;
    if (pid > 0)
    {
        printf("pid de l'exec command = %d\n", pid);
        waitpid(pid, &status, 0);
        garbage->ret = status / 256;
        parent_process(garbage, s_cmd, ex);
        if ((s_cmd->prev_sep && ex->infile) || (s_cmd->prev_sep && ex->outfile))
        {
            close_files(ex);
        }
    }
	else
        child_process(garbage, s_cmd, ex, paths);
}
