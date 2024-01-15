/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:22:34 by flavian           #+#    #+#             */
/*   Updated: 2024/01/15 10:57:08 by flavian          ###   ########.fr       */
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

typedef struct arg
{
	char		**line;
	char		*sep;
	char		*prev_sep;
	struct arg	*next;
}			t_arg;

typedef struct garbage_colector
{
	t_prompt	*prpt;
	t_bui		*blts;
	t_arg		*arg;
	char		*line;
	int			nb_exec;
	int			ret;
	int			fd_hdoc;
	int			go;
	int			end;
}					t_gc;

typedef struct t_new_arg
{
	t_arg	*tmp;
	t_arg	*ret_next;
	t_arg	*first_to_free;
	t_arg	*rest_to_free;
	int		sep_val;
	int		next_sep_val;
}			t_na;

typedef struct s_copy_str
{
	int		y;
	char	*quote;
	int		size;
}			t_cs;

typedef struct pars
{
	char	*av;
	char	**env;
	int		i;
}			t_pars;

typedef struct s_size_for_line
{
	int		i;
	char	*tmp;
	char	*quote;
	int		count;
}			t_sfl;

typedef struct s_size_for_malloc_del
{
	char	*tmp;
	int		set;
	int		i;
}			t_sfmd;

typedef struct s_get_del_hdoc
{
	int		i;
	int		y;
	char	*quote;
	int		size;
}			t_gdh;

typedef struct s_handle_quotes
{
	char	*buf;
	int		end;
	int		y;
	int		i;
}			t_hq;

typedef struct s_new_str
{
	int		len;
	int		i;
	int		y;
	int		set;
}				t_ns;


typedef struct s_get_line
{
	int	y;
	int	word_count;
}				t_sl;

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

typedef struct count_word
{
	int		count;
	int		i;
	int		set;
	char	*quote;
}			t_wc;

typedef struct exec
{
	int		*infile;
	int		i;
	int		*outfile;
	int		o;
	char	**paths;
	int		r;
	int		*pipex;
	int		p;
	int		idx;
	int		nb_pipe;
}			t_exec;

void	close_standard_fd(void);

char	*ft_prompt(void);
int		clear_or_exit(char **str);

int		is_builtins(t_gc *garbage, char **args);
t_gc	*in_minishell(void);

t_bui	*set_builtins(void);
int		ft_env(t_gc *garbage, char **args);
int		ft_pwd(t_gc *garbage, char **args);
int		ft_export(t_gc *garbage, char **args, int porc);
int		ft_unset(t_gc *garbage, char **args, int k);
int		ft_cd(t_gc *garbage, char **args);
int		ft_cd_2(t_gc *garbage, char **args);
int		ft_echo(t_gc *garbage, char **args);
int		ft_echo_2(t_gc *garbage, char **args);
int		ft_put_ret_value(t_gc *garbage, char **args);
int		ft_define_var(t_gc *garbage, char **args);

int		is_builtins(t_gc *garbage, char **args);

int		print_env(t_gc *garbage);
int		set_env(t_bui *blts);
char	**create_env(char **existing_env);

void	free_all(t_gc *garbage);
void	free_blts(t_bui *blts);
void	free_t_exec(t_exec *ex);
void	free_tab(char **env);
void	exit_error(t_gc *garbage);

int		signal_init(int pid_minishell);
int		signal_init_child(void);
void	signal_handler_child(int signum);

int		ft_strlen_tab(char **env);
char	*get_pwd(void);
int		ft_size_var_env(char *str);
int		check_var_exist(char **tableau, char *arg);
int		it_is_an_equal(char *str);
int		update_var(t_bui *blts, char *arg, int j);
char	**ft_sort_tab(char **tabl);

char	*remove_quote(char *str);
int		add_var_env(t_bui *blts, char *arg);
int		update_var_env(t_bui *blts, char *str);
int		update_env(t_bui *blts);

char	**ft_sort_tab_n_add_dbq(char **tabl);
char	*add_db_quote(char *src);
void	ft_swap(char **a, char **b);
int		ft_strcmp(char *s1, char *s2);

int		set_export(t_bui *blts);	//export.c
int		update_export(t_gc *garbage, char **args);
int		replace_old_exp(t_bui *blts, char *arg_w_db_q);

int		new_var_w_value(t_bui *blts, char *arg);	//utiles_export.c
int		new_name_var(t_bui *blts, char *arg);
int		check_arg_should_be_define(char *arg);

int		del_var_unset(t_gc *garbage, char **args, int k);
int		go_to_find_var_and_del(t_bui *blts, char *str);

int		cd_set_pwd(t_bui *blts);

int		ft_open(char *file, int typeofsep);

void	exit_child(t_gc *garbage, t_exec *ex);
void	ft_cmd_not_find(char **paths, char *cmd, t_gc *garbage, t_exec *ex);

int		init_open(t_exec *ex, t_arg *s_cmd, int typeofsep, t_gc *garbage);

t_arg	*main_pars(char *str, t_bui *blts, t_gc *garbage);		//pars.c
t_arg	*parsing(t_pars *pars, t_gc *garbage);
t_arg	*create_arg(t_pars *pars, int ret_val);

void	free_parsing(t_arg *cmd);		//p_free.c
void	print_cmd(t_arg *cmd);
void	free_pars_tab(char **arr);
int		ft_error(char *msg, int ret);
void	free_victime(t_arg *cmd);


int		is_printable(char c);		//p_is.c
int		is_whitespace(char c);
int		is_sep(char c);
int		is_var_env(char c);
int		is_quote(char c);

char	**strduptab(t_pars *pars);		//p_utils.c
char	*ms_strjoin(char *s1, char *s2, int status);
int		ms_strjoin_size(char *s1, char *s2, int size);
int		ms_strcmp(char *s1, char *s2, int n);
// char	*no_quote(t_pars *pars);

int		env_strncmp(char *s1, char *s2, int n);

int		ft_strcmp(char *s1, char *s2);

int		get_var_env_2(t_pars *pars, int i);			//p_utils_2.c
int		ft_strncmp_ms(char *s1, char *s2, int size, int l);
t_arg	*post_parsing(t_arg *arg);

int		count_char(t_pars *pars);		//p_count.c
int		count_word(t_pars *pars);
int		count_sep(t_pars *pars);

char	*get_in_env(char **env, char *str, int ret_val);	//p_env.c
char	*get_var_env(t_pars *pars, int i, int ret_val);
int		after_var_env(t_pars *pars, int i);
char	*is_ret_val(char *str, int ret_val);

char	*get_sep(t_pars *pars);			//p_sep.c
int		get_sep_size(t_pars *pars);
void	too_many_sep(t_pars *pars);
int		check_sep(char *sep);

char	**get_line(t_pars *pars, int ret_val);		//p_line.c
char	*copy_str(t_pars *pars, int ret_val);
int		size_for_line(t_pars *pars, int ret_val);

int		quote_is_closed(t_pars *pars, int l);		//p_quote.c
char	*handle_quotes(t_pars *pars, int l);
int		count_quote(t_pars *pars);

char	*get_del_hdoc(t_pars *pars, int l);		//p_hdoc.c
int		get_here_doc(char *av, int fd);
int		size_for_del(t_pars *pars, int l);
int		scan_av_for_hdoc(t_pars *pars, int fd_hdoc);
char	*handle_quotes_hdoc(t_pars *pars, int l);

int		pipex(int ac, char **av, t_exec *ex, t_gc *garbage);
int		init_pipex(t_exec *ex, t_arg *s_cmd, t_gc *garbage);
void	put_respipex(t_exec *ex);

void	ft_exec(t_arg *s_cmd, char **paths, t_gc *garbage, t_exec *ex);
void	close_files(t_exec *ex);
int		init_t_exec(t_exec *ex, t_arg *s_cmd, t_gc *garbage);
void	ft_init_exec(t_arg *s_cmd, t_gc *garbage, t_exec *ex);
int		ft_lstsize_targ(t_arg *lst);
void	reset_line(char **tabl, t_gc *garbage);
int		count_sep_exec(t_arg *s_cmd, char *sep1, char *sep2);
void	set_pipex(t_arg *s_cmd, t_gc *garbage, t_exec *ex);
int		check_sep_exec(char *sep, t_exec *ex);

void	print_arg(t_arg *arg);
char	*new_str(t_pars *pars, int ret_val);
t_arg	*new_arg(t_exec *ex, t_arg *arg);
t_arg	*open_to_free(t_arg *to_free, t_exec *ex);
int		set_sep_val(t_na *n_a, t_arg *arg, t_exec *ex);

char	*get_cmd(char **paths, char	**cmd, t_gc *garbage, t_exec *ex);
char	*find_path(char **envp);
int		ft_strcmp(char *s1, char *s2);
void	close_pipes(t_exec *ex);
int		signal_init_main(void);
void	signal_handler_child(int signum);
void	signal_handler_main(int signum);
int		loop_echo_write(char **args, int i, t_gc *garbage);
void	ret_value_exit(char *nbr, int i, int ret_value, t_gc *garbage);
void	free_t_pars(t_pars *pars);

#endif