
#include "../includes/minishell.h"

int	set_export(t_bui *blts)
{
	blts->exp = ft_sort_tab(blts->env);
	if (!blts->exp)
	{
		free_blts(blts);
		return (1);
	}
	return (0);
}