/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:39:23 by fserpe            #+#    #+#             */
/*   Updated: 2023/12/21 10:07:04 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strncmp_ms(char *s1, char *s2, int size, int l)
{
	int	i;

	i = 0;
	if (size == 0)
		return (0);
	if (!s1 || !s2)
		return (1);
	while (s1[l + i] == s2[i] && i < size - 1 && s1[l + i] && s2[i])
	{
		++i;
	}
	return (s1[l + i] - s2[i]);
}

int	get_var_env_2(t_pars *pars, int i)
{
	int	y;

	y = 0;
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !is_sep(pars->av[i]) && !is_quote(pars->av[i]))
	{
		y++;
		i++;
	}
	return (y);
}
