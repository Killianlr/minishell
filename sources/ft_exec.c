/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:09 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/05 18:41:53 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void    put_respipex()
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
    unlink(".res_pipex");
}

void    set_fd(t_exec *ex)
{
    // write(2, "in set_fd\n", 11);
    if (ex->infile && ex->infile[ex->i] > 0)
	{
		if (ex->r)
		{
			dup2(ex->infile[ex->i], ex->res_pipex);
            close(ex->res_pipex);
		}
		else
        {
	        // printf("fd in set fd= %d\n", ex->infile[ex->i]);

			dup2(ex->infile[ex->i], STDIN_FILENO);
        }
	}
	if (ex->outfile && ex->outfile[ex->o] > 0)
	{
        printf("outfile = %d\n", ex->outfile[ex->o]);
	    dup2(ex->outfile[ex->o], STDOUT_FILENO);
    }
}

void    parent_process(t_gc *garbage, t_arg *s_cmd, t_exec *ex)
{
    (void) ex;
    // char    buf[4096];
    // int ret;
    // ret = 879;
    ft_export(garbage, s_cmd->line, 1);
    ft_define_var(garbage, s_cmd->line);
	ft_unset(garbage, s_cmd->line);
    ft_cd(garbage, s_cmd->line);
    // close(ex->tube[1]);
    // ret = read(ex->tube[0], buf, 4096);
    // printf("buf = %s\n", buf);
    // close(ex->tube[0]);
    // printf("ret = %d\n", ret);
    // garbage->ret = ft_atoi(buf);
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
        // printf("ici cmd not find\n");
        ft_cmd_not_find(paths, s_cmd->line[0], garbage, ex);
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
    if(pipe(ex->tube) < 0)
        return ;
    if (pid > 0)
    {
        waitpid(pid, NULL, 0);
        parent_process(garbage, s_cmd, ex);
    }
	else
	{
        child_process(garbage, s_cmd, ex, paths);
	}
}
