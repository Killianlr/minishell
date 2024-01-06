/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:02:50 by flavian           #+#    #+#             */
/*   Updated: 2024/01/06 20:43:48 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		return (-1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	if (s1[i + 1] && s1[i + 1] != '=')
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
	s1[i + y] = 0;
	free(s2);
	return (1);
}

void	ms_strjoin_free(char *s1, char *s2, int status)
{
	if (status == 1)
		free(s1);
	else if (status == 2)
		free(s2);
	else if (status == 3)
	{
		free(s1);
		free(s2);
	}
}

char	*ms_strjoin_2(char *s1, char *s2)
{
	char	*str;
	int		len_s1 = ft_strlen(s1);
	int		len_s2 = ft_strlen(s2);

	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	int i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	int y = 0;
	while (s2[y])
	{
		str[i + y] = s2[y];
		y++;
	}
	str[i + y] = '\0';
	return (str);
}

char	*ms_strjoin(char *s1, char *s2, int status)
{
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = ms_strjoin_2(s1, s2);
	if (!str)
		return (NULL);
	ms_strjoin_free(s1, s2, status);
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
