/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:19:07 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:29:53 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (!g_signal || g_signal == 130)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_signal)
			printf("\n");
		g_signal = 130;
	}
	else if (signum == SIGQUIT)
	{
		if (g_signal && g_signal != 130)
		{
			write(1, "Quit (core dumped)\n", 20);
		}
		else
			write(1, "\b\b  \b\b", 7);
	}
}

int	signal_init(void)
{
	if (signal(SIGINT, signal_handler))
		return (1);
	if (signal(SIGQUIT, signal_handler))
		return (1);
	return (0);
}
