/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:47:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/11/17 11:53:14 by kle-rest         ###   ########.fr       */
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
	int		here_doc;
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
void	free_pipe(t_p *pip);
void	close_pipes(t_p *pip);
void	free_child(t_p *pip);
void	free_parent(t_p *pip);
void	free_main(t_p *pip);
int		msg_error(char *str, t_p *pip);
int		pi_strcmp(char *s1, char *s2, int n);
void	get_here_doc(char *av, t_p *pip);
char	*get_cmd(char **paths, char	**cmd, char **envp);
void	child(t_p pip, char **av, char **envp);

#endif