/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 15:25:42 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/15 10:53:11 by flavian          ###   ########.fr       */
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

void	ret_value_exit(char *nbr, int i, int ret_value, t_gc *garbage)
{
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
		{
			printf("minishell: exit: %s: numeric argument required\n", nbr);
			free_all(garbage);
			exit(2);
		}
		i++;
	}
	ret_value = ft_atoi(nbr);
	if (ret_value > 0)
	{
		while (ret_value > 256)
			ret_value -= 256;
	}
	else if (ret_value < 0)
	{
		ret_value *= -1;
		while (ret_value > 256)
			ret_value -= 256;
		ret_value = 256 - ret_value;
	}
	free_all(garbage);
	exit(ret_value);
}

int	loop_echo_write(char **args, int i, t_gc *garbage)
{
	while (args[i] && args[i + 1])
	{
		if (!ft_strncmp(args[i], "$?", 4))
			ft_putnbr_fd(garbage->ret, STDOUT_FILENO);
		else
		{
			write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
			write(STDOUT_FILENO, " ", 1);
			i++;
		}
	}
	return (i);
}
