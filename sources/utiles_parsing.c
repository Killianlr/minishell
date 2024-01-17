#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	if ((c != '\n' && c > 9 && c < 14) || c == ' ')
		return (1);
	else
		return (0);
}

int	is_char(char c)
{
	if (!c)
		return (0);
	if (ft_find_sep_val(c))
		return (0);
	if (is_whitespace(c))
		return (0);
	return (1);
}

int	ft_find_sep_val(char c)
{
	if (!c)
		return (0);
	else if (c == '|')
		return (1);
	else if (c == '<')
		return (2);
	else if (c == '>')
		return (3);
	return (0);
}

int	new_val_i(s_pars *pars, int i)
{
	while (pars->av[i] && (ft_find_sep_val(pars->av[i]) > 1
			|| is_whitespace(pars->av[i])))
		i++;
	while (pars->av[i] && !is_whitespace(pars->av[i])
			&& !ft_find_sep_val(pars->av[i]))
		i++;
	return (i);
}

int	ft_count_pipe(char *str)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_find_sep_val(str[i]) == 1)
			count++;
		i++;
	}
	return (count);
}