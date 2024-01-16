
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
	free_tab(garbage->args); /* FREE PARSING*/
	free_blts(garbage->blts);
	free(garbage->blts);
	// if (garbage->fd_hdoc)
	// 	unlink(".heredoc_tmp");
	free(garbage);
	close_standard_fd();
}

void	exit_free(t_gc *garbage, int exival)
{
	printf("exit_free, exit = %d\n", exival);
	free_all(garbage);
	exit(exival);
}

void	exit_child(t_gc *garbage, int exival)
{
	printf("exit_child, exit = %d\n", exival);
	free_all(garbage);
	exit(exival);
}

void	close_standard_fd(void)
{
	close(0);
	close(1);
	close(2);
}