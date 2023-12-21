/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:43 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 11:15:22 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	clear_or_exit(char **str)
{
	if (!str)
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
	if (!args)
		return (0);
	if (ft_env(garbage, args))
		return (1);
	if (ft_pwd(garbage, args))
		return (1);
	if (ft_export(garbage, args))
		return (1);
	if (ft_unset(garbage, args))
		return (1);
	if (ft_cd(garbage, args))
		return (1);
	if (ft_echo(garbage, args))
		return (1);
	if (ft_define_var(garbage, args))
		return (1);
	ft_put_ret_value(garbage, args);
	return (0);
}

int	test(t_arg *s_cmd)
{
	t_arg	*tmp;
	int		i;

	if (!s_cmd->sep && !s_cmd->next)
		return (0);
	if (s_cmd->sep && !s_cmd->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	tmp = s_cmd->next;
	while (tmp->next)
	{
		i = 0;
		if (tmp->sep && !tmp->next)
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (1);
		}
		while (tmp->line[0] && tmp->line[0][i])
		{
			if (!ft_isalnum(tmp->line[0][i]))
			{
				printf("minishell: syntax error near unexpected token `%c'\n", tmp->line[0][i]);
				return (1);
			}
			i++;
		}
		tmp = tmp->next;
	}
	i = 0;
	if (tmp->sep && !tmp->next)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	while (tmp->line[0] && tmp->line[0][i])
	{
		printf("tmp->line[0][%d] %c\n", i, tmp->line[0][i]);
		if (!ft_isalnum(tmp->line[0][i]))
		{
			printf("minishell: syntax error near unexpected token `%c'\n", tmp->line[0][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_lstsize_targ(t_arg *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

int	loop_lst(char *str, t_arg *s_cmd, t_gc *garbage)
{
	int	i;
	t_arg	*save;

	if (!str)
		return (0);
	save = s_cmd;
	i = ft_lstsize_targ(s_cmd);
	while (i)
	{
		if (clear_or_exit(s_cmd->line))
			return (1);
		if (is_builtins(garbage, s_cmd->line))
			return (1);
		s_cmd = s_cmd->next;
		i--;
	}
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
	garbage->ret = 0;
	while (1)
	{
		garbage->arg = NULL;
		garbage->line = ft_prompt();
		if ((int)ft_strlen(garbage->line))
			garbage->arg = main_pars(garbage->line, garbage->blts, garbage);
		free(garbage->line);
		// if (test(garbage->arg))
		// 	garbage->arg->line = NULL;
		if (loop_lst(garbage->line, garbage->arg, garbage))
			break ;
	}
	return (garbage);
}

int	main(void)
{
	t_gc	*garbage;

	if (clear_terminal())
		return (1);
	if (signal_init())
		return (1);
	garbage = in_minishell();
	free_all(garbage);
	return (0);
}
