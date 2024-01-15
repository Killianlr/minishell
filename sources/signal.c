/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:19:07 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 10:45:08 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	signal_init_child(void)
{
	if (signal(SIGQUIT, SIG_IGN))
		return (1);
	return (0);
}

void	signal_handler_child(int signum)
{
	int	i;

	i = 1000000;
	if (signum == SIGINT)
	{
		while (i)
			i--;
	}
	else if (signum == SIGQUIT)
	{
	}
}

int	signal_init_main(void)
{
	if (!signal(SIGINT, signal_handler_main))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
