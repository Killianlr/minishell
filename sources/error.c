/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:58:11 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/14 18:52:07 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage, t_exec *ex)
{
	(void) ex;
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	close_standard_fd();
	free_tab(paths);
	free_all(garbage);
	exit(127);
}

void	exit_child(t_gc *garbage, t_exec *ex)
{
	close_files(ex);
	close_pipes(ex);
	free_t_exec(ex);
	close_standard_fd();
	free_all(garbage);
	exit(1);
}
