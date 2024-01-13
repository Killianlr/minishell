/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/13 18:51:49 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	ft_exit(t_gc *garbage, char **args)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	if (!args[1])
	{
		free_all(garbage);
		exit(0);
	}
	if (args[2])
	{
		free_all(garbage);
		printf("minishell: exit: too many arguments\n");
		exit(1);
	}
	if (args[1][i] == '-')
		i++;
	ret_value_exit(args[1], i, ret_value, garbage);
}

int	loop_lst(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
	if (clear_or_exit(s_cmd->line))
	{
		free_tab(ex->paths);
		ft_exit(garbage, s_cmd->line);
		return (1);
	}
	if (garbage->go)
		ft_init_exec(s_cmd, garbage, ex);
	else if (!garbage->go)
		garbage->go = 1;
	waitpid(-1, NULL, 0);
	return (0);
}

int	init_and_loop_lst(char *str, t_arg *s_cm, t_gc *garbage)
{
	t_exec	ex;
	t_arg	*s_cmd;

	if (!str || !s_cm)
		return (0);
	s_cmd = s_cm;
	if (init_t_exec(&ex, s_cmd, garbage))
		return (1);
	garbage->nb_exec = ft_lstsize_targ(s_cmd);
	while (garbage->nb_exec)
	{
		if (loop_lst(s_cmd, garbage, &ex))
			return (1);
		if (s_cmd->next)
			s_cmd = s_cmd->next;
		garbage->nb_exec--;
	}
	free_t_exec(&ex);
	garbage->arg = s_cm;
	free_parsing(garbage->arg);
	return (0);
}

int	loop_in_minishell(t_gc *garbage)
{
	garbage->fd_hdoc = 0;
	garbage->go = 1;
	garbage->arg = NULL;
	garbage->line = ft_prompt();
	if (!garbage->line)
	{
		free_all(garbage);
		return (1);
	}
	if ((int)ft_strlen(garbage->line))
		garbage->arg = main_pars(garbage->line, garbage->blts, garbage);
	free(garbage->line);
	if (init_and_loop_lst(garbage->line, garbage->arg, garbage))
	{
		free_all(garbage);
		return (1);
	}
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
	signal_init_child();
	garbage->nb_exec = 0;
	garbage->ret = 0;
	while (1)
	{
		if (loop_in_minishell(garbage))
			return (NULL);
	}
	return (garbage);
}
