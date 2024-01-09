/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:09:57 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/09 16:10:57 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_empty(char *str)
{
	int	len;
	int	i;

	if (!str)
		return (1);
	i = 0;
	len = ft_strlen(str);
	if (len == 0)
		return (1);
	while (i < len)
	{
		if (str[i] > 32 && str[i] < 127)
			return (0);
		i++;
	}
	return (1);
}
