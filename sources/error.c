/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:58:11 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/10 11:14:50 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage, t_exec *ex)
{
	(void) ex;
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	close_standard_fd();
	free_tab(paths);
	free_all(garbage);
	exit(127);
}

void	exit_child(t_gc *garbage, t_exec *ex)
{
	close_files(ex);
	close_standard_fd();
	free_all(garbage);
	exit(1);
}

void	msg_error_close(t_p *pip, t_exec *ex)
{
	close(pip->infile);
	close(pip->outfile);
	unlink(".res_pipex");
	if (!ex->infile)
		unlink(".infile_tmp");
}

int	msg_error_2(char *str, t_p *pip)
{
	int	i;

	write(2, str, ft_strlen(str));
	i = 0;
	while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
	if (pip->args)
		free(pip->args);
	if (pip->cmd)
		free(pip->cmd);
	close(pip->outfile);
	unlink(".res_pipex");
	exit (1);
}

int	msg_error(char *str, t_p *pip, t_exec *ex)
{
	int	i;

	write(2, str, ft_strlen(str));
	i = 0;
	while (pip->args && pip->args[i])
	{
		free(pip->args[i]);
		i++;
	}
	while (pip->path && pip->path[i])
	{
		free(pip->path[i]);
		i++;
	}
	if (pip->path)
		free(pip->path);
	if (pip->args)
		free(pip->args);
	if (pip->cmd)
		free(pip->cmd);
	msg_error_close(pip, ex);
	exit (1);
}
