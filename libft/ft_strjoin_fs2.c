/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_fs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:45:30 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/09 16:09:46 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_fs2_next(char *s1, char *s2, char *str)
{
	int	i;
	int	y;

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
	return (str);
}

char	*ft_strjoin_fs2(char *s1, char *s2)
{
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (s2);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	str = ft_strjoin_fs2_next(s1, s2, str);
	free(s2);
	return (str);
}
