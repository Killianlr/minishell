/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/11 14:46:22 by kle-rest         ###   ########.fr       */
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

typedef struct 	s_prompt
{
	char	*inpt;
	char	*str;
}				t_prompt;

typedef struct 	s_builtins
{
	int		exi_env;
	char	**env;
	char	**exp;
	char	*pwd;
}				t_bui;

typedef struct 	garbage_colector
{
	t_prompt *prpt;
	t_bui	*blts;
	char	**args;
	char			*line;
}				t_gc;

char	*ft_prompt();

int		clear_terminal();


t_gc	*in_minishell();

t_bui   *set_builtins(void);
int		ft_env(t_gc *garbage, char **args);
int		ft_pwd(t_gc *garbage, char **args);
int		ft_export(t_gc *garbage, char **args);


int		print_env(t_gc *garbage);
int		set_env(t_bui *blts);



void	free_all(t_gc *garbage);
void	free_blts(t_bui *blts);
void    free_tab(char **env);

int		signal_init(void);

int		ft_strlen_tab(char **env);
char    *get_pwd(void);
int		ft_size_var_env(char *str);
int		check_var_exist(char **tableau, char *arg);
int		it_is_an_equal(char *str);
int		update_var(t_bui *blts, char *arg, int j);


char	*remove_quote(char *str);
int		add_var_env(t_bui *blts, char *arg);
int		update_var_env(t_bui *blts, char *str);

char	**ft_sort_tab(char **tabl);
char	*add_db_quote(char *src);

int		set_export(t_bui *blts);
int		update_export(t_gc *garbage, char **args);

#endif