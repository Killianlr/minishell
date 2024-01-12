/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:47:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/12 16:17:23 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_running = 0;

void	signal_handler_main(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_running = 1;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

void	signal_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_running = 1;
	}
	else if (signum == SIGQUIT)
	{
	}
}

int	signal_init_main(int pid_minishell)
{
	while (!g_running)
	{
		if (signal(SIGINT, signal_handler_main))
			return (1);
		if (signal(SIGQUIT, signal_handler_main))
			return (1);
	}
	g_running = 0;
	kill(pid_minishell, SIGTERM);
	return (0);
}

int	main_parent(void)
{
	t_gc	*garbage;
	int		pid_minishell;
	int		status;

	while (1)
	{
		pid_minishell = fork();
		if (pid_minishell < 0)
			break ;
		else if (pid_minishell == 0)
		{
			garbage = in_minishell();
			if (!garbage)
			{
				close_standard_fd();
				exit(1);
			}
			free_all(garbage);
		}
		else
		{
			signal_init_main(pid_minishell);
		}
		waitpid(pid_minishell, &status, 0);
		if (status > 255 || status == 0)
			break ;
	}
	return (status / 256);
}

int	main(void)
{
	int		pid_main;
	int		ret;

	
	pid_main = fork();
	if (pid_main < 0)
		return (1);
	else if (pid_main == 0)
	{
		close_standard_fd();
		exit(0);
	}
	else
	{
		ret = main_parent();
	}
	close_standard_fd();
	return (ret);
}
