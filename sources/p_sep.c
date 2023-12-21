/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_sep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:49:43 by flavian           #+#    #+#             */
/*   Updated: 2023/12/21 10:06:50 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_sep_error(char c, int *val)
{
	free(val);
	ft_printf("Minishell: syntax error near unexpected token '%c'\n", c);
	return (-1);
}

int	check_sep_2(char *sep, int *val, int len)
{
	int	i;

	i = 0;
	if (len == 2 && val[i + 1])
	{
		if (val[i] == 1 && val[i + 1] == 1)
			return (print_sep_error(sep[i + 1], val));
		if (val[i] == 2 && val[i + 1] != 2)
			return (print_sep_error(sep[i + 1], val));
		if (val[i] == 3 && val[i + 1] == 2)
			return (print_sep_error(sep[i + 1], val));
	}
	if (len == 3 && val[i + 2])
	{
		if (val[i] == 1 && val[i + 1] == 2 && val[i + 2] == 2)
		{
			free(val);
			return (1);
		}
		else
			return (print_sep_error(sep[i + 2], val));
	}
	free(val);
	return (1);
}

int	check_sep(char *sep)
{
	int	i;
	int	len;
	int	*val;

	if (!sep)
		return (0);
	len = ft_strlen(sep);
	i = 0;
	if (len >= 4)
	{
		ft_printf("Minishell: syntax error near unexpected token '%c'\n",
			sep[len]);
		return (-1);
	}
	val = malloc(sizeof(int) * len);
	if (!val)
		return (-1);
	while (i < len)
	{
		val[i] = is_sep(sep[i]);
		i++;
	}
	return (check_sep_2(sep, val, len));
}

int	get_sep_size(t_pars *pars)
{
	int	i;
	int	count;

	i = pars->i;
	count = 0;
	while (pars->av[i] && !is_sep(pars->av[i]))
		i++;
	while (pars->av[i] && is_sep(pars->av[i]))
	{
		count++;
		i++;
	}
	return (count);
}

char	*get_sep(t_pars *pars)
{
	char	*buf;
	int		y;

	buf = malloc(sizeof(char) * (get_sep_size(pars) + 1));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	y = 0;
	while (pars->av[pars->i] && !is_sep(pars->av[pars->i]))
		pars->i++;
	if (!pars->av[pars->i])
	{
		free(buf);
		return (NULL);
	}
	while (pars->av[pars->i] && is_sep(pars->av[pars->i]))
		buf[y++] = pars->av[pars->i++];
	buf[y] = 0;
	return (buf);
}
