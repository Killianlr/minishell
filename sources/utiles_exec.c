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

int	pi_strcmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	if (n != (int)ft_strlen(s2) - 1)
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static int	find_max_int_tab(char **env)
{
	int		r;

	r = 0;
	while (env[r])
		r++;
	return (r);
}

static char	*find_path_2(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_path(char **envp)
{
	int	r;
	int	max;

	r = 0;
	max = find_max_int_tab(envp);
	while (r < max && ft_strncmp("PATH", envp[r], 4))
		r++;
	if (r == max)
		return (NULL);
	else
		return (find_path_2(envp));
	return (NULL);
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