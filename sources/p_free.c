/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:17:12 by flavian           #+#    #+#             */
/*   Updated: 2024/01/13 18:08:04 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_arg(t_arg *arg)
{
	t_arg	*tmp;

	if (!arg)
		return ;
	tmp = arg->next;
	while (tmp)
	{
		printf("111\n");
		if (arg->line)
		{
			for (int i = 0; arg->line[i]; i++)
				printf("line[i] = %s[%i]\n", arg->line[i], i);			
		}
		printf("sep = %s\n", arg->sep);
		printf("prev sep = %s\n", arg->prev_sep);
		arg = arg->next;
		tmp = arg;
	}
	if (arg->line)
	{
		for (int i = 0; arg->line[i]; i++)
			printf("line[i] = %s[%i]\n", arg->line[i], i);			
	}
	printf("sep = %s\n", arg->sep);
	printf("prev sep = %s\n", arg->prev_sep);
}

void	free_pars_tab(char **arr)
{
	int	i;

	i = 0;
	if (!arr[i])
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

int	ft_error(char *msg, int ret)
{
	if (msg)
		ft_printf("%s\n", msg);
	return (ret);
}

void	free_victime(t_arg *cmd)
{
	if (cmd->line)
		free_pars_tab(cmd->line);
	if (cmd->sep)
		free(cmd->sep);
	if (cmd->prev_sep)
		free(cmd->prev_sep);
	free(cmd);
}

void	free_parsing(t_arg *cmd)
{
	t_arg	*tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		if (cmd->line)
			free_pars_tab(cmd->line);
		if (cmd->sep)
			free(cmd->sep);
		if (cmd->prev_sep)
			free(cmd->prev_sep);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	if (cmd->line)
		free_pars_tab(cmd->line);
	if (cmd->sep)
		free(cmd->sep);
	if (cmd->prev_sep)
		free(cmd->prev_sep);
	free(cmd);
}
