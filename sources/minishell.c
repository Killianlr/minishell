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

int	loop_lst(t_arg *s_cmd, t_gc *garbage, t_exec *ex)
{
	if (clear_or_exit(s_cmd->line))
	{
		free_tab(ex->paths);
		return (1);
	}
	if (garbage->go)
		ft_init_exec(s_cmd, garbage, ex);
	else if (!garbage->go)
		garbage->go = 1;
	waitpid(-1, NULL, 0);
	if (s_cmd->next)
		s_cmd = s_cmd->next;
	garbage->nb_exec--;
	return (0);
}

int	init_and_loop_lst(char *str, t_arg *s_cm, t_gc *garbage)
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
		if (loop_lst(s_cmd, garbage, &ex))
			return (1);
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
