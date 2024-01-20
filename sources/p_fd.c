/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:35:36 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/20 12:25:22 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*find_file_name_2(t_pars *pars, int i, int y, int len, char *quote)
{
	char	*ret;

	ret = ft_calloc(len + 1, 1);
	if (!ret)
		return (NULL);
	y = 0;
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !ft_find_sep_val(pars->av[i]))
	{
		if (is_quote(pars->av[i]))
		{
			quote = handle_quotes(pars->av, i);
			if (!quote)
				return (NULL);
			if (!ms_strj_s(ret, quote, len))
				return (NULL);
			y = ft_strlen(ret);
			i = end_quote(pars->av, i) + 1;
			if (!pars->av[i])
				break ;
		}
		ret[y++] = pars->av[i++];
	}
	ret[y] = 0;
	return (ret);
}

char	*find_file_name(t_pars *pars, int i)
{
	char	*ret;
	char	*quote;
	int		len;
	int		y;

	ret = NULL;
	quote = NULL;
	while (pars->av[i] && (ft_find_sep_val(pars->av[i]) > 1
			|| is_whitespace(pars->av[i])))
		i++;
	if (!pars->av[i])
		return (0);
	len = 0;
	y = i;
	while (pars->av[y] && !is_whitespace(pars->av[y])
		&& !ft_find_sep_val(pars->av[y]))
	{
		if (is_quote(pars->av[y]))
		{
			quote = handle_quotes(pars->av, y);
			len += ft_strlen(quote);
			free(quote);
			y = end_quote(pars->av, y);
		}
		len++;
		y++;
	}
	return (find_file_name_2(pars, i, y, len, quote));
}

void	set_fd_parsing(t_cmd *cmd, char *file_name, int type_of_sep)
{
	if (type_of_sep == 1 || type_of_sep == 3)
	{
		if (cmd->fd_in)
		{
			close(cmd->fd_in);
			cmd->fd_in = parsing_open(file_name, type_of_sep, cmd);
		}
		else
			cmd->fd_in = parsing_open(file_name, type_of_sep, cmd);
	}
	if (type_of_sep == 2 || type_of_sep == 4)
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

	i = pars->i;
	if (ft_find_sep_val(pars->av[i]) == 1)
		i++;
	type_of_sep = 0;
	while (pars->av[i] && ft_find_sep_val(pars->av[i]) != 1)
	{
		if (ft_find_sep_val(pars->av[i]) > 1)
		{
			file_name = find_file_name(pars, i);
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
