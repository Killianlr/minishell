/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:45:10 by flavian           #+#    #+#             */
/*   Updated: 2023/12/01 21:52:28 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**strduptab(char *src, int i)
{
	char **dup;
	int	y;

	if (!src || !src[i])
		return (NULL);
	dup = malloc(sizeof(char *) * 2);
	if (!dup)
		return (NULL);
	dup[0] = malloc(sizeof(char) * ft_strlen(src) + 1);
	y = 0;
	while (src[i] && !is_sep(src[i]))
		dup[0][y++] = src[i++];
	dup[0][y] = 0;
	dup[1] = NULL;

	return (dup);
}