/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mspars.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 11:20:05 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSPARS_H
# define MSPARS_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "../libft/libft.h"

typedef struct cmd
{
	char	**line;
	char	*sep;
	struct cmd	*next;
}			t_cmd;

t_cmd	*parsing(char *str);

void	free_parsing(t_cmd *cmd);

void	print_cmd(t_cmd *cmd);

	
int	is_sep(char c);

#endif