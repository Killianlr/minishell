/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/17 20:19:30 by flavian          ###   ########.fr       */
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
// #include "mspars.h"

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

typedef struct arg
{
	char	**line;
	char	*sep;
	char	*h_doc;
	struct arg	*next;
}			t_arg;

typedef struct pars
{
	char	*av;
	char	**env;
	int		i;
}			t_pars;

typedef struct 	garbage_colector
{
	t_prompt *prpt;
	t_bui	*blts;
	t_arg	*arg;
	char			*line;
}				t_gc;


char	*ft_prompt();

int		clear_terminal();

t_gc	*in_minishell();

t_bui   *set_builtins(void);
int		ft_env(t_gc *garbage);
int		ft_pwd(t_gc *garbage);
int		ft_export(t_gc *garbage);


int		print_env(t_gc *garbage);
int		set_env(t_bui *blts);



void	free_all(t_gc *garbage);
void	free_blts(t_bui *blts);
void    free_tab(char **env);

int		signal_init(void);

int		ft_strlen_tab(char **env);
char    *get_pwd(void);
int		ft_size_var_env(char *str);
int		check_var_exist(t_gc *garbage, char *arg);

char	*remove_quote(char *str);
int		add_var_env(t_bui *blts, char *arg);

char	**ft_sort_tab(char **tabl);
char	*add_db_quote(char *src);

int		set_export(t_bui *blts);
int		update_export(t_gc *garbage);



t_arg	*main_pars(char *str, t_bui *blts);
t_arg	*parsing(t_pars *pars);
void	free_parsing(t_arg *cmd);
void	print_cmd(t_arg *cmd);
int		is_printable(char c);
int		is_whitespace(char c);
int		is_sep(char c);
int		is_var_env(char c);
int		is_quote(char c);
char	**strduptab(t_pars *pars);;
int		count_char(t_pars *pars);
int		count_word(t_pars *pars);
int		count_sep(t_pars *pars);
char	*get_in_env(char **env, char *str);
char	*get_var_env(t_pars *pars, int i);
int		after_var_env(t_pars *pars, int i);
char	*get_sep(t_pars *pars);
char	**get_line(t_pars *pars);
int		quote_is_closed(t_pars *pars, int l);
char	*handle_quotes(t_pars *pars, int l);
int		count_quote(t_pars *pars);
void	too_many_sep(t_pars *pars);
char	*copy_str(t_pars *pars);
char	*ms_strjoin(char *s1, char *s2, int status);
char	*ms_strjoin_len(char *s1, char *s2, int status, int len);
char	*is_here_doc(t_pars *pars);
int		ms_strcmp(char *s1, char *s2, int n);
char	*get_here_doc(char *av);






#endif