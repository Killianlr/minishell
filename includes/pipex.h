/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:39:50 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 15:04:27 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_p
{
	int		infile;
	int		outfile;
	int		cmd_nbr;
	int		pipe_nbr;
	int		idx;
	int		pid;
	int		*pipe;
	char	**path;
	char	**args;
	char	*cmd;	
}t_p;

char	*find_path(char **envp);
void	free_pipe(t_p *pip, t_exec *ex);
void	close_pipes(t_p *pip);
void	free_child(t_p *pip);
void	free_parent(t_p *pip);
void	free_main(t_p *pip, t_exec *ex, char **av);
int		msg_error(char *str, t_p *pip, t_exec *ex);
int		msg_error_2(char *str, t_p *pip);
int		pi_strcmp(char *s1, char *s2, int n);
char	*get_cmd(char **paths, char	**cmd, char **envp);
void	child(t_p pip, char **av, char **envp);

#endif