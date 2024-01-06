/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/06 20:20:46 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int running = 0;

int	clear_or_exit(char **str)
{
	
	if (!str || !str[0])
		return (0);
	if (!ft_strncmp("clear", str[0], ft_strlen(str[0])))
	{
		if (str[1])
		{
			if (!ft_strncmp("history", str[1], ft_strlen(str[1])))
				rl_clear_history();
		}
	}
	if (!ft_strncmp("exit", str[0], 4) && ft_strlen(str[0]) == 4)
		return (1);
	else
		return (0);
}

int	is_builtins(t_gc *garbage, char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	i = ft_env(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_pwd(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_export(garbage, args, 0);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_unset(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_cd(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_echo(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	i = ft_define_var(garbage, args);
	if (i == 1)
		exit_error(garbage);
	else if (i == 2)
		return (2);
	// i = ft_put_ret_value(garbage, args);
	// if (i == 1)
	// 	exit_error(garbage);
	// else if (i == 2)
	// 	return (2);
	return (0);
}

int	loop_lst(char *str, t_arg *s_cm, t_gc *garbage)
{
	t_exec	ex;
	t_arg	*s_cmd;

	if (!str || !s_cm)
		return (0);
	s_cmd = s_cm;
	garbage->nb_exec = ft_lstsize_targ(s_cmd);
	if (init_t_exec(&ex, s_cmd, garbage))
        return (1);
	while (garbage->nb_exec)
	{
		if (clear_or_exit(s_cmd->line))
		{
			free_tab(ex.paths);
			return (1);
		}
		if (garbage->go)
			ft_init_exec(s_cmd, garbage, &ex);
		else if (!garbage->go)
			garbage->go = 1;
		waitpid(-1, NULL, 0);
		if (s_cmd->next)
			s_cmd = s_cmd->next;
		garbage->nb_exec--;
	}
	free_t_exec(&ex);
	// free_tab(ex.paths);
	garbage->arg = s_cm;
	free_parsing(garbage->arg);
	return (0);
}

t_gc	*in_minishell(void)
{
	t_gc	*garbage;

	garbage = malloc(sizeof(t_gc));
	if (!garbage)
		return (NULL);
	garbage->blts = set_builtins();
	if (!garbage->blts)
	{
		free(garbage);
		return (NULL);
	}
	garbage->nb_exec = 0;
	garbage->ret = 0;
	garbage->fd_hdoc = 0;
	while (1)
	{
		garbage->go = 1;
		garbage->arg = NULL;
		garbage->line = ft_prompt();
		if (!garbage->line)
			return (NULL);
		if ((int)ft_strlen(garbage->line))
			garbage->arg = main_pars(garbage->line, garbage->blts, garbage);
		free(garbage->line);
		if (loop_lst(garbage->line, garbage->arg, garbage))
			return (NULL);
	}
	return (garbage);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		running = 1;
	}
	else if (signum == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 7);
	}
}

int	signal_init(int	pid_minishell)
{
	while (!running)
	{
		if (signal(SIGINT, signal_handler))
			return (1);
		if (signal(SIGQUIT, signal_handler))
			return (1);
	}
	running = 0;
	kill(pid_minishell, SIGTERM);
	return (0);
}

int	main(void)
{
	t_gc	*garbage;
	int		pid_main;
	int		pid_minishell;
	int		status;

	if (clear_terminal())
		return (1);
	status = 0;
	pid_main = fork();
	if (pid_main < 0)
		return (printf("error\n"));
	else if (pid_main == 0)
		exit(0);
	else
	{
		while (1)
		{
			pid_minishell = fork();
			if (pid_minishell < 0)
				break ;
			else if (pid_minishell == 0)
			{
				garbage = in_minishell();
				if (!garbage)
					exit(1);
				free_all(garbage);
			}
			else
				signal_init(pid_minishell);
			waitpid(pid_minishell, &status, 0);
			if (status > 255)
				break ;
		}
	}
	return (0);
}
