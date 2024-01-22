/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2024/01/22 19:06:30 by fserpe           ###   ########.fr       */
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

typedef struct s_cmd
{
	char			**line;
	int				fd_in;
	int				fd_out;
	int				hdoc;
	struct s_cmd	*next;
}					t_cmd;

typedef struct garbage_colector
{
	t_prompt	*prpt;
	t_bui		*blts;
	t_cmd		*s_cmd;
	char		*line;
	int			ret;
	int			pipe;
}					t_gc;

typedef struct s_pars
{
	char	*av;
	char	**env;
	int		i;
}			t_pars;

typedef struct s_handle_quotes
{
	char	*buf;
	int		end;
	int		y;
	int		i;
}			t_hq;

typedef struct s_count_quote
{
	int	i;
	int	set;
	int	s_count;
	int	d_count;
}				t_sq;

typedef struct s_get_in_env
{
	char	*buf;
	int		i;
	int		y;
	int		j;
}			t_gie;

typedef struct s_new_str
{
	char	*quote;
	int		len;
	int		i;
	int		y;
	int		set;
}				t_ns;

typedef struct s_fill_cmd_line
{
	int		set;
	int		y;
	int		size;
	char	*quote;
}			t_fcl;

typedef struct s_len_for_malloc_line
{
	int		i;
	int		set;
	char	*quote;
}			t_lfmf;

typedef struct s_find_file_name
{
	char	*quote;
	int		len;
	int		y;
}			t_ffn;

typedef struct s_size_for_line
{
	int		i;
	char	*tmp;
	char	*quote;
	int		count;
}			t_sfl;

/*---------------------------p_free.c-------------------------*/

int		ft_error(char *msg, int ret);
t_cmd	*end_of_pars(t_pars *pars, t_cmd *cmd);

/*---------------------------parsing.c-------------------------*/

t_cmd	*parsing(t_gc *garbage);
char	*check_sep_count(char *str);

/*---------------------------p_utiles.c-------------------------*/

int		ft_find_sep_val(char c);
int		ft_count_pipe(char *str);
int		new_val_i(t_pars *pars, int i);
int		is_char(char c);
void	print_cmd(t_cmd *cmd);
int		ms_strcmp(char *s1, char *s2, int n);
int		env_strncmp(char *s1, char *s2, int n);
char	*ms_strjoin(char *s1, char *s2, int status);
int		ms_strj_s(char *s1, char *s2, int size);
char	*strjoin_env(char *s1, char *s2, int size);


/*---------------------------p_error.c-------------------------*/

char	*handle_quotes_error(t_hq *data);
char	**get_cmd_line_error(char **ret);
int		error_file_sep(char *str, int i);

/*---------------------------p_quote.c-------------------------*/

int		end_quote(char *str, int l);
char	*handle_quotes(char *str, int l);
int		size_for_quote(char *str);
int		count_quote(char *str);

/*---------------------------p_new_str.c-------------------------*/

char	*new_str(t_pars *pars, int ret_val);

/*---------------------------p_len_mal.c-------------------------*/

int		len_for_malloc_line(t_pars *pars);
int		len_for_malloc_tab(t_pars *pars);

/*---------------------------p_hdoc.c-------------------------*/

char	*get_var_env(t_pars *pars, int i, int ret_val);
int		get_here_doc(char *av, int fd, t_cmd *cmd);

/*---------------------------p_env.c-------------------------*/

char	*is_ret_val(char *str, int ret_val);

/*---------------------------p_get_in_env.c-------------------------*/

char	*get_in_env(char **env, char *str, int ret_val);

/*---------------------------p_is.c-------------------------*/

int		is_quote(char c);
int		is_var_env(char c);
int		is_sep(char c);
int		is_printable(char c);
int		is_whitespace(char c);

/*---------------------------p_open.c-------------------------*/

int		parsing_open(char *file, int typeofsep, t_cmd *cmd);

/*---------------------------p_fd.c-------------------------*/

int		set_cmd_fd(t_pars *pars, t_cmd *cmd);
char	**get_cmd_line(t_pars *pars);
int		check_fd(t_cmd *cmd, t_gc *garbage);

/*---------------------------p_file_name.c-------------------------*/

char	*find_file_name(t_pars *pars, int i);

/*---------------------------prompt.c-------------------------*/

char	*ft_prompt(t_gc *garbage);

/*---------------------------free.c-------------------------*/

void	free_all(t_gc *garbage);
void	free_tab(char **tableau);
void	free_blts(t_bui *blts);
void	exit_free(t_gc *garbage, int exival);
void	close_standard_fd(void);
void	exit_child(t_gc *garbage, int exival);
void	free_cmd(t_cmd *cmd);

/*---------------------------signal.c-------------------------*/

int		signal_init(void);
void	signal_handler(int signum);
void	signal_handler_exec(int signum);

/*---------------------------builtins_check.c-------------------------*/

int		is_builtins(t_gc *garbage, char **args, int pid);
void	ft_exit(t_gc *garbage, char **args);
int		ft_strcmp(char *s1, char *s2);

/*---------------------------builtins_1.c-------------------------*/

t_bui	*set_builtins(void);
int		ft_define_var(t_gc *garbage, char **args, int pid);
int		ft_unset(t_gc *garbage, char **args);
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

int		del_var_unset(t_gc *garbage, char **args);
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
void	relativ_of_absolut(t_gc *garbage, char **cmd, char **paths);
char	*check_current_dir(char *cmd);
int		isdirectory(char *path);

/*---------------------------ft_sort_tab_n_add_dbq.c-------------------------*/

char	**ft_sort_tab_n_add_dbq(char **tabl);
char	*add_db_quote(char *src);
void	ft_swap(char **a, char **b);

/*---------------------------setup_exec.c-------------------------*/

int		setup_exec(t_gc *garbage, t_cmd *cmd, int nb_cmd);
char	*get_cmd(char **paths, char	**cmd, t_gc *garbage);

/*---------------------------setup_pipe.c-------------------------*/

int		run_pipe(t_gc *garbage, t_cmd *cmd, int fdd, int nb_cmd);

/*---------------------------utiles_exec.c-------------------------*/

int		ft_lstsize_cmd(t_cmd *lst);
void	set_fd(t_cmd *cmd);
void	wait_child_status(t_gc *garbage, int pid, int status);
char	*rln(char *cmd, char *pwd, DIR *directory, struct dirent *entry);

#endif