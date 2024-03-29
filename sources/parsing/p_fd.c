/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:35:36 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/21 16:01:22 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_type_of_sep(t_pars *pars, int i)
{
	int	ret;
	int	set;

	ret = 0;
	set = 0;
	while (pars->av[i] && ft_find_sep_val(pars->av[i])
		&& !is_whitespace(pars->av[i]))
	{
		if (!set && ft_find_sep_val(pars->av[i]) == 2)
			ret = 1;
		else if (!set && ft_find_sep_val(pars->av[i]) == 3)
			ret = 2;
		else if (set && ft_find_sep_val(pars->av[i]) == 2)
			ret = 3;
		else if (set && ft_find_sep_val(pars->av[i]) == 3)
			ret = 4;
		i++;
		set = ft_find_sep_val(pars->av[i]);
	}
	return (ret);
}

void	set_fd_parsing(t_cmd *cmd, char *file_name, int type_of_sep)
{
	if (type_of_sep == 1 || type_of_sep == 3)
	{
		if (cmd->fd_in)
		{
			if (cmd->hdoc)
			{
				unlink(".heredoc_tmp");
				cmd->hdoc = 0;
			}
			close(cmd->fd_in);
			cmd->fd_in = parsing_open(file_name, type_of_sep, cmd);
		}
		else
			cmd->fd_in = parsing_open(file_name, type_of_sep, cmd);
	}
	else if (type_of_sep == 2 || type_of_sep == 4)
	{
		if (cmd->fd_out)
		{
			close(cmd->fd_out);
			cmd->fd_out = parsing_open(file_name, type_of_sep, cmd);
		}
		else
			cmd->fd_out = parsing_open(file_name, type_of_sep, cmd);
	}
}

int	set_cmd_fd(t_pars *pars, t_cmd *cmd)
{
	int		i;
	char	*file_name;
	int		type_of_sep;
	int		quote;
	int		set;

	i = pars->i;
	if (ft_find_sep_val(pars->av[i]) == 1)
		i++;
	type_of_sep = 0;
	set = 0;
	quote = 0;
	while (pars->av[i] && ft_find_sep_val(pars->av[i]) != 1)
	{
		if (is_quote(pars->av[i]) && set == 0)
		{
			quote = is_quote(pars->av[i]);
			set = 1;
		}
		else if (is_quote(pars->av[i]) == quote && set == 1)
		{
			quote = 0;
			set = 0;
		}
		else if (ft_find_sep_val(pars->av[i]) > 1 && set == 0)
		{
			file_name = find_file_name(pars, i);
			printf("file_name = %s\n", file_name);
			if (!file_name)
				return (0);
			type_of_sep = find_type_of_sep(pars, i);
			set_fd_parsing(cmd, file_name, type_of_sep);
			free(file_name);
			i = new_val_i(pars, i);
			if (!pars->av[i])
				return (1);
		}
		i++;
	}
	return (1);
}
