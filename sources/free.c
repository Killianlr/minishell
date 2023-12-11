
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
}

void	free_blts(t_bui *blts)
{
    free(blts->env);
	free(blts->exp);
	free(blts->pwd);
}

void	free_all(t_gc *garbage)
{
	printf("DEBUT DU FREE\n");
	if (!garbage)
		return ;
	// free(garbage->line);
	free_tab(garbage->blts->env);
	printf("avant free tab export\n");
	free_tab(garbage->blts->exp);
	printf("apres free tab export\n");
	free_tab(garbage->args);
	free(garbage->args);
	free_blts(garbage->blts);
	free(garbage->blts);
	free(garbage);
	printf("FIN DU PROGRAMME\n");
}