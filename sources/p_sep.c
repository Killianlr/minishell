/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_sep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:49:43 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 15:20:16 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
