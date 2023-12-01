/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2023/11/24 14:47:11 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

int	signal_ctrl_c;

typedef struct s_term
{
	char *term_type;
	char *term_args[2];
}t_term;

typedef struct s_prompt
{
	char	*inpt;
	char	*str;
}t_prompt;

typedef struct garbage_colector
{
	struct s_prompt *prpt;
	char			*line;
}t_gc;

char	*ft_prompt();

int		clear_terminal();

int    ctrl_c();

void	in_minishell();

#endif