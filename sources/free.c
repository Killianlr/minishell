
#include "../includes/minishell.h"

void	free_tab(char **tableau)
{
	int	i;

	i = 0;
	while (tableau && tableau[i])
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_blts(t_bui *blts)
{
	free_tab(blts->env);
	free_tab(blts->exp);
	free(blts->pwd);
}

void	free_all(t_gc *garbage)
{
	if (!garbage)
		return ;
	// free_parsing(garbage->arg);
	//free_tab(garbage->args); /* FREE PARSING*/
	if (garbage->s_cmd->hdoc > 0)
	{
		write(2, "HERE\n", 6);
		unlink(".heredoc_tmp");
	}
	if (garbage->s_cmd)
		free_cmd(garbage->s_cmd);
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage);
	close_standard_fd();
}

void	free_cmd(s_cmd *cmd)
{
	s_cmd *tmp;

	if (!cmd)
		return ;
	tmp = cmd->next;
	while (tmp)
	{
		if (cmd->fd_in > 0)
			close(cmd->fd_in);
		if (cmd->fd_out > 0)
			close(cmd->fd_out);
		free_tab(cmd->line);
		free(cmd);
		cmd = tmp;
		tmp = cmd->next;
	}
	if (cmd->fd_in > 0)
		close(cmd->fd_in);
	if (cmd->fd_out > 0)
		close(cmd->fd_out);
	free_tab(cmd->line);
	free(cmd);
}

void	exit_free(t_gc *garbage, int exival)
{
	// printf("exit_free, exit = %d\n", exival);
	free_all(garbage);
	exit(exival);
}

void	exit_child(t_gc *garbage, int exival)
{
	// printf("exit_child, exit = %d\n", exival);
	free_all(garbage);
	exit(exival);
}

void	close_standard_fd(void)
{
	close(0);
	close(1);
	close(2);
}