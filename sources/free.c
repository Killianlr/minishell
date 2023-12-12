
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

void	exit_error(t_gc *garbage)
{
	printf("debut free error\n");
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage->line);
	free_tab(garbage->args);
	free(garbage);
	printf("fin free error\n");
	exit(0);
}

void	free_all(t_gc *garbage)
{
	printf("DEBUT DU FREE\n");
	if (!garbage)
		return ;
	// free(garbage->line);
	free_blts(garbage->blts);
	free(garbage->blts);
	free_tab(garbage->args);
	free(garbage);
	printf("FIN DU PROGRAMME\n");
}