/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:47:05 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/15 13:56:30 by kle-rest         ###   ########.fr       */
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
		while (i)
			i--;
		g_running = 1;
	}
	else if (signum == SIGQUIT)
	{
	}
}

void	sub_child(void)
{
	t_gc	*garbage;

	garbage = NULL;
	garbage = in_minishell();
	if (!garbage)
	{
		close_standard_fd();
		exit(1);
	}
	free_all(garbage);
}

int	sub_parent(int pid_minishell, int status)
{
	while (!g_running)
	{
		signal_init_main();
		waitpid(pid_minishell, &status, WNOHANG);
		if (status > 255 || status == 0)
			return (status);
	}
	g_running = 0;
	kill(pid_minishell, SIGTERM);
	waitpid(pid_minishell, NULL, 0);
	return (status);
}

int	main_parent(void)
{
	int		pid_minishell;
	int		status;

	while (1)
	{
		status = 1;
		pid_minishell = fork();
		if (pid_minishell < 0)
			break ;
		else if (pid_minishell == 0)
			sub_child();
		else
		{
			status = sub_parent(pid_minishell, status);
			if (status > 255 || status == 0)
				break ;
		}
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
