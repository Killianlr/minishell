/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:53:41 by fserpe            #+#    #+#             */
/*   Updated: 2024/01/21 13:51:23 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_free(t_gc *garbage, int exival)
{
	free_all(garbage);
	exit(exival);
}

void	exit_child(t_gc *garbage, int exival)
{
	free_all(garbage);
	exit(exival);
}
