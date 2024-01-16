#ifndef PARSING_H
# define PARSING_H

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

typedef struct t_pars
{
	char	*av;
	char	**env;
	int		i;
}			s_pars;

typedef struct t_cmd
{
	char **line;
	int		fd_in;
	int		fd_out;
	struct t_cmd	*next;
}			s_cmd;



s_cmd	*parsing(char *str);     //parsing.c

int		ft_find_sep_val(char c);     //p_utils.c
int		ft_count_pipe(char *str);
int		is_whitespace(char c);
int		new_val_i(s_pars *pars, int i);
int		is_char(char c);
void	print_cmd(s_cmd *cmd);

void	free_cmd(s_cmd *cmd);



int	parsing_open(char *file, int typeofsep);     //p_open.c

int	set_cmd_fd(s_pars *pars, s_cmd *cmd);     //p_fd.c

char	**get_cmd_line(s_pars *pars);


#endif