/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2023/12/15 14:36:37 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

int	g_signal;

typedef struct s_prompt
{
	char	*inpt;
	char	*str;
}				t_prompt;

typedef struct s_builtins
{
	int		exi_env;
	char	**env;
	char	**exp;
	char	*pwd;
	int		upwd;
	int		uoldpwd;
}				t_bui;

typedef struct garbage_colector
{
	t_prompt	*prpt;
	t_bui		*blts;
	char		**args;
	char		*line;
	int			ret;
}					t_gc;

/*---------------------------prompt.c-------------------------*/

char	*ft_prompt(t_gc *garbage);

/*---------------------------free.c-------------------------*/

void	free_all(t_gc *garbage);
void	free_tab(char **tableau);
void	free_blts(t_bui *blts);
void	exit_free(t_gc *garbage, int exival);
void	close_standard_fd(void);
void	exit_child(t_gc *garbage, int exival);

/*---------------------------signal.c-------------------------*/

int		signal_init(void);

/*---------------------------builtins_check.c-------------------------*/

int		is_builtins(t_gc *garbage, char **args, int pid);
void	ft_exit(t_gc *garbage, char **args);
int		ft_strcmp(char *s1, char *s2);

/*---------------------------builtins_1.c-------------------------*/

t_bui	*set_builtins(void);
int		ft_define_var(t_gc *garbage, char **args, int pid);
int		ft_unset(t_gc *garbage, char **args, int pid);
int		ft_export(t_gc *garbage, char **args, int pid);
int		ft_env(t_gc *garbage, char **args, int pid);

/*---------------------------builtins_2.c-------------------------*/

int		ft_echo(t_gc *garbage, char **args, int pid);
int		option_echo(char *tiret_n);
int		ft_cd(t_gc *garbage, char **args, int pid);
int		ft_pwd(t_gc *garbage, char **args, int pid);

/*---------------------------builtins_utiles.c-------------------------*/

char	*get_pwd(void);
int		ft_strlen_tab(char **env);
int		ft_size_var_env(char *str);
int		update_var(t_bui *blts, char *arg, int j);
int		check_var_exist(char **tableau, char *arg);

/*---------------------------cd.c-------------------------*/

int		cd_set_pwd(t_bui *blts);

/*---------------------------env.c-------------------------*/

int		set_env(t_bui *blts);
int		update_var_env(t_bui *blts, char *str);

/*---------------------------export.c-------------------------*/

int		set_export(t_bui *blts);
int		update_export(t_gc *garbage, char **args, int pid);

/*---------------------------unset.c-------------------------*/

int		del_var_unset(t_gc *garbage, char **args, int k);
int		go_to_find_var_and_del(t_bui *blts, char *str);

/*---------------------------utiles_env_1.c-------------------------*/

int		update_env(t_bui *blts);
int		print_env(t_gc *garbage);
char	*remove_quote(char *str);

/*---------------------------utiles_env_2.c-------------------------*/

char	**create_env(char **existing_env);
int		add_var_env(t_bui *blts, char *arg);
int		it_is_an_equal(char *str);

/*---------------------------utiles_export.c-------------------------*/

int		replace_old_exp(t_bui *blts, char *arg_w_db_q);
char	**ft_sort_tab(char **tabl);
int		check_arg_should_be_define(char *arg);
int		new_name_var(t_bui *blts, char *arg);
int		new_var_w_value(t_bui *blts, char *arg);

/*---------------------------utiles_path.c-------------------------*/

char	*find_path(char **envp);

/*---------------------------ft_sort_tab_n_add_dbq.c-------------------------*/

char	**ft_sort_tab_n_add_dbq(char **tabl);
char	*add_db_quote(char *src);
void	ft_swap(char **a, char **b);

/*---------------------------setup_exec.c-------------------------*/

int		setup_exec(t_gc *garbage, char **cmd);


#endif