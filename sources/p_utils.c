/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:02:50 by flavian           #+#    #+#             */
/*   Updated: 2023/12/19 12:45:06 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ms_strcmp(char *s1, char *s2, int n)
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

int	ms_strjoin_size(char *s1, char *s2, int size)
{
	int		i;
	int		y;

	if (size < 0)
		return (0);
	if (!s1)
		return (0);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	y = 0;
	while (s2[y] && i + y < size)
	{
		s1[i + y] = s2[y];
		y++;
	}
	free(s2);
	return (1);
}

char	*ms_strjoin(char *s1, char *s2, int status)
{
	char	*str;
	int		i;
	int		y;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
	{
		str[i + y] = s2[y];
		y++;
	}
	str[i + y] = 0;
	if (status == 1)
		free(s1);
	else if (status == 2)
		free(s2);
	else if (status == 3)
	{
		free(s1);
		free(s2);
	}
	return (str);
}

char	**strduptab(t_pars *pars)
{
	char	**dup;
	int		y;

	if (!pars->av || !pars->av[pars->i])
		return (NULL);
	dup = malloc(sizeof(char *) * 2);
	if (!dup)
		return (NULL);
	dup[0] = malloc(sizeof(char) * 2);
	y = 0;
	dup[0][y++] = ' ';
	dup[0][y] = 0;
	dup[1] = NULL;
	return (dup);
}
