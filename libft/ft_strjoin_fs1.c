/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fs1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:33:14 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:33:19 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_fs1(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		y;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	y = 0;
	while (s2[y])
	{
		str[i + y] = s2[y];
		++y;
	}
	str[i + y] = 0;
	free(s1);
	return (str);
}
