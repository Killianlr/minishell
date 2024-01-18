
#include "../includes/minishell.h"

int	ft_lstsize_cmd(s_cmd *lst)
{
	int	size;

	size = 0;
	if (!lst)
		return (0);
	while (lst->next)
	{
		lst = lst->next;
		size++;
	}
	if (lst)
		size++;
	return (size);
}