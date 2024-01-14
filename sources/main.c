/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:47:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/13 19:06:49 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_running = 0;

void	signal_handler_main(int signum)
{
	int	i;

	i = 1000000;
	if (signum == SIGINT)
	{
		printf("\n");
		while(i)
			i--;
		g_running = 1;
	}
	else if (signum == SIGQUIT)
	{
	}
}

void	signal_handler_child(int signum)
{
	int	i;

	i = 1000000;
	if (signum == SIGINT)
	{
		while(i)
			i--;
	}
	else if (signum == SIGQUIT)
	{
	}
}

int	signal_init_main()
{
	if (!signal(SIGINT, signal_handler_main))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	main_parent(void)
{
	t_gc	*garbage;
	int		pid_minishell;
	int		status;

	while (1)
	{
		status = 1;
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
		while (!g_running)
		{
			signal_init_main();
			waitpid(pid_minishell, &status, WNOHANG);
			if (status > 255 || status == 0)
				break ;
		}
		g_running = 0;
		kill(pid_minishell, SIGTERM);
		waitpid(pid_minishell, NULL, 0);
		if (status > 255 || status == 0)
			break ;
	}
	return (status / 256);
}

int	main(void)
{
	int		pid_main;
	int		ret;

	g_running = 0;
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
