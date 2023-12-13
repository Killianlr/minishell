/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:02:50 by flavian           #+#    #+#             */
/*   Updated: 2023/12/13 14:25:06 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	exist_in_env(char *str, int i, t_bui *blts)
// {
// 	int	y;

// 	if (!str[i])
// 		return (0);
// 	y = 0;
// 	while (blts->env[y])
// 	{
// 		if (!ft_strncmp(str + i, blts->env[y]))
// 	}
// }

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

char	**strduptab(char *src, int i)
{
	char **dup;
	int	y;

	if (!src || !src[i])
		return (NULL);
	dup = malloc(sizeof(char *) * 2);
	if (!dup)
		return (NULL);
	dup[0] = malloc(sizeof(char) * 2);
	y = 0;
	if (src[i] && !is_sep(src[i]))
		dup[0][y++] = src[i];
	dup[0][y] = 0;
	dup[1] = NULL;
	return (dup);
}