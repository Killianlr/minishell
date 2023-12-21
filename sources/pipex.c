/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:55:48 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/21 11:40:20 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/pipex.h"

void	get_pipes(t_p *pip)
{
	int	i;

	i = 0;
	while (i < pip->cmd_nbr - 1)
	{
		if (pipe(pip->pipe + 2 * i) < 0)
			free_parent(pip);
		i++;
	}
}

int	pipex(int ac, char **av, t_exec *ex, char **envp)
{
	t_p	pip;
	int	i = 0;

	if (ex->infile[ex->i])
		pip.infile = ex->infile[ex->i];
	else
		pip.infile = -1;
	pip.outfile = ex->res_pipex;
	pip.cmd_nbr = ac;
	printf("dans pipex\n");
	while(av[i])
	{
		printf("av[%d] %s\n", i, av[i]);
		i++;
	}
	printf("infile = %d\n", pip.infile);
	printf("outfile = %d\n", pip.outfile);
	printf("nb_cmd = %d\n", pip.cmd_nbr);
	pip.pipe_nbr = 2 * (pip.cmd_nbr - 1);
	printf("pipe_nbr = %d\n", pip.pipe_nbr);
	pip.pipe = malloc(sizeof(int) * pip.pipe_nbr);
	if (!pip.pipe)
		msg_error("error pipe\n", &pip);
	pip.path = ft_split(find_path(envp), ':');
	if (!pip.path)
		free_pipe(&pip);
	get_pipes(&pip);
	pip.idx = -1;
	while (++(pip.idx) < pip.cmd_nbr)
		child(pip, av, envp);
	close_pipes(&pip);
	free_main(&pip);
	waitpid(-1, NULL, 0);
	return (0);
}
