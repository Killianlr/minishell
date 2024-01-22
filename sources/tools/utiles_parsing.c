/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:18:33 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/22 19:14:48 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_strcmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (-1);
	if (n != (int)ft_strlen(s2) - 1)
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_char(char c)
{
	if (!c)
		return (0);
	if (ft_find_sep_val(c))
		return (0);
	if (is_whitespace(c))
		return (0);
	if (is_quote(c))
		return (0);
	return (1);
}

int	ft_find_sep_val(char c)
{
	if (!c)
		return (0);
	else if (c == '|')
		return (1);
	else if (c == '<')
		return (2);
	else if (c == '>')
		return (3);
	return (0);
}

int	new_val_i(t_pars *pars, int i)
{
	while (pars->av[i] && (ft_find_sep_val(pars->av[i]) > 1
			|| is_whitespace(pars->av[i])))
		i++;
	while (pars->av[i] && !is_whitespace(pars->av[i])
		&& !ft_find_sep_val(pars->av[i]))
	{
		if (is_quote(pars->av[i]))
			i = end_quote(pars->av, i);
		i++;
	}
	return (i);
}

int	ft_count_pipe(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			i = end_quote(str, i);
		else if (ft_find_sep_val(str[i]) == 1)
		{
			if (!str[i + 1])
			{
				printf("minishell: expected char after `|'\n");
				return (-1);
			}
			count++;
		}
		i++;
	}
	return (count);
}
