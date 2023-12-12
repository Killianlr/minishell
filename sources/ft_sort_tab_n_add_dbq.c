/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:53:08 by kle-rest          #+#    #+#             */
/*   Updated: 2022/10/04 11:03:54 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void    ft_swap(char **a, char **b)
{
	char	*s;

	s = *a;
	*a = *b;
	*b = s;
}

char	*add_db_quote(char *src)
{
	char	*dest;
	int		i;
	int		q;

	i = 0;
	q = 0;
	dest = malloc(sizeof(char) * (ft_strlen(src) + 3));
	if (!dest)
		return (0);
	while (src[i])
	{
		if (src[i] == '=' && q == 0 && src[i + 1] != '"')
		{
			dest[i + q] = src[i];
			i++;
			dest[i + q] = '"';
			q++;
		}
		else
		{
			dest[i + q] = src[i];
			i++;
		}
	}
	if (src[i - 1] != '"')
	{
		dest[i + q] = '"';
		dest[i + q + 1] = 0;
	}
	else
		dest[i] = 0;
	return (dest);
}

char	**ft_sort_tab_n_add_dbq(char **tabl)
{
	int	i;
	char	**sorted_tab;

	i = 0;
	sorted_tab = malloc(sizeof(char *) * (ft_strlen_tab(tabl) + 1));
	if (!sorted_tab)
		return (NULL);
	while (i < ft_strlen_tab(tabl) - 1)
	{
		if (ft_strcmp(tabl[i], tabl[i + 1]) > 0)
		{
			ft_swap(&tabl[i], &tabl[i + 1]);
			i = 0;
		}
		i++;
	}
	i = 0;
	while (i < ft_strlen_tab(tabl))
	{
		sorted_tab[i] = add_db_quote(tabl[i]);
		if (!sorted_tab[i])
			return (NULL);
		i++;
	}
	sorted_tab[i] = NULL;
	return (sorted_tab);
}
