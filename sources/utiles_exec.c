/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:38:35 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/05 17:30:57 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

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
	close(pip->infile);
	close(pip->outfile);
	unlink(".res_pipex");
	if (!ex->infile)
		unlink(".infile_tmp");
	exit (1);
}

int	ft_lstsize_targ(t_arg *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void	reset_line(char **tabl, t_gc *garbage)
{
	int		i;
	char	*save;

	if (!tabl[1])
		garbage->go = 0;
	i = 0;
	save = tabl[0];
	if (ft_strlen_tab(tabl) <= 1)
		return ;
	while (tabl[i])
	{
		tabl[i] = tabl[i + 1];
		i++;
	}
	free(save);
	tabl[i] = NULL;
}

int count_sep_exec(t_arg *s_cmd, char *sep1, char *sep2)
{
    int i;

    i = 0;
    while (s_cmd->next)
    {
        if (!ft_strncmp(s_cmd->sep, sep1, 3) || !ft_strncmp(s_cmd->sep, sep2, 3))
            i++;
        s_cmd = s_cmd->next;
    }
    return (i);
}