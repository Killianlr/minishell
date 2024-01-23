/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:35:36 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/23 12:14:49 by kle-rest         ###   ########.fr       */
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
				unlink_hdoc(cmd);
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

int	is_redir_fd(t_pars *pars, t_cmd *cmd, t_gc *garbage, t_scf *data)
{
	(void) cmd;
	data->type_of_sep = find_type_of_sep(pars, data->i);
	data->file_name = find_file_name(pars, data->i);
	if (!data->file_name)
		return (error_file_sep(pars->av, data->i, garbage));
	set_fd_parsing(cmd, data->file_name, data->type_of_sep);
	free(data->file_name);
	data->i = new_val_i(pars, data->i);
	return (1);
}

int	loop_set_cmd_fd(t_pars *pars, t_cmd *cmd, t_gc *garbage, t_scf *data)
{
	while (pars->av[data->i] && ft_find_sep_val(pars->av[data->i]) != 1)
	{
		if (is_quote(pars->av[data->i]) && data->set == 0)
		{
			data->quote = is_quote(pars->av[data->i]);
			data->set = 1;
		}
		else if (is_quote(pars->av[data->i]) == data->quote && data->set == 1)
		{
			data->quote = 0;
			data->set = 0;
		}
		else if (ft_find_sep_val(pars->av[data->i]) > 1 && data->set == 0)
		{
			if (!is_redir_fd(pars, cmd, garbage, data))
				return (0);
			if (!pars->av[data->i])
				return (1);
		}
		data->i++;
	}
	return (1);
}

int	set_cmd_fd(t_pars *pars, t_cmd *cmd, t_gc *garbage)
{
	t_scf	*data;

	data = malloc(sizeof(t_scf));
	if (!data)
		return (-1);
	data->i = pars->i;
	if (ft_find_sep_val(pars->av[data->i]) == 1)
		data->i++;
	data->type_of_sep = 0;
	data->set = 0;
	data->quote = 0;
	if (!loop_set_cmd_fd(pars, cmd, garbage, data))
	{
		free(data);
		return (0);
	}
	free(data);
	return (1);
}
