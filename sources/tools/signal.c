/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:19:07 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/21 13:53:37 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signum)
{
	extern int	g_signal;

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
}

int	signal_init(void)
{
	if (signal(SIGINT, signal_handler))
		return (1);
	if (signal(SIGQUIT, SIG_IGN))
		return (1);
	return (0);
}

void	signal_handler_exec(int signum)
{
	extern int	g_signal;

	if (signum == SIGINT)
	{
		g_signal = 130;
	}
	else if (signum == SIGQUIT)
	{
	}
}
