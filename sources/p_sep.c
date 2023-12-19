/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_sep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:49:43 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 14:01:53 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	too_many_sep(t_pars *pars)
{
	char	*buf;
	int		is_print;
	int		y;
	int		i;

	i = pars->i;
	y = pars->i;
	is_print = 0;
	while (pars->av[y] && is_whitespace(pars->av[y]) && !is_sep(pars->av[y]))
	{
		if (is_printable(pars->av[y]))
		{
			is_print = 1;
			break ;
		}
		y++;
	}
	if (pars->av[y] && y > i && is_print == 1 && !is_sep(pars->av[y]))
		return ;
	buf = malloc(sizeof(char) * 3);
	if (!buf)
		return ;
	y = 0;
	while (pars->av[i] && is_whitespace(pars->av[i]))
		i++;
	if (pars->av[i] && is_sep(pars->av[i]))
		buf[y++] = pars->av[i];
	if ((pars->av[i] == '<' || pars->av[i] == '>')
		&& (pars->av[i] == pars->av[i + 1]))
		buf[y++] = pars->av[++i];
	buf[y] = 0;
	if (!buf[0])
		printf("Minishell: syntax error near unexpected token `%s'\n", buf);
	free(buf);
	return ;
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
