#include "parsing.h"

int	len_for_malloc_tab(s_pars *pars)
{
	int	len;
	int	i;
	int	set;

	len = 0;
	set = 0;
	i = pars->i;
	while (pars->av[i] && ft_find_sep_val(pars->av[i]) != 1)
	{
		if (set == 0 && is_char(pars->av[i]))
		{
			set = 1;
			len++;
		}
		else if (set == 0 && ft_find_sep_val(pars->av[i]) > 1)
			i = new_val_i(pars, i) - 1;
		else if (set == 1 && is_whitespace(pars->av[i])
				|| ft_find_sep_val(pars->av[i]) > 1)
			set = 0;
		i++;
	}
	printf("len for tab = %d\n", len);
	return (len);
} 

int	len_for_malloc_line(s_pars *pars)
{
	int	i;
	int	len;
	int	set;

	i = pars->i;
	len = 0;
	set = 0;
	while (pars->av[i] && ft_find_sep_val(pars->av[i]) != 1)
	{
		if (ft_find_sep_val(pars->av[i]) > 1)
			i = new_val_i(pars, i) - 1;
		else if (is_char(pars->av[i]))
		{
			set = 1;
			len++;
		}
		else if (set == 1 && !is_char(pars->av[i]))
			return (len);
		i++;
	}
	return (len);
}

char	*fill_cmd_line(s_pars *pars)
{
	char	*ret;
	int		len;
	int		set;
	int		y;

	printf("in fill cmd line\n");
	ret = malloc(sizeof(char) * (len_for_malloc_line(pars) + 1));
	if (!ret)
		return (NULL);
	y = 0;
	set = 0;
	while (pars->av[pars->i] && ft_find_sep_val(pars->av[pars->i]) != 1)
	{
		if (ft_find_sep_val(pars->av[pars->i]) > 1)
			pars->i = new_val_i(pars, pars->i) - 1;
		else if (is_char(pars->av[pars->i]))
		{
			set = 1;
			ret[y] = pars->av[pars->i];
			y++;
		}
		else if (set == 1 && !is_char(pars->av[pars->i]))
			break ;
		pars->i++;
	}
	ret[y] = 0;
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

void	new_val_pars_i(s_pars *pars)
{
	while (pars->av[pars->i] && !is_char(pars->av[pars->i]) && ft_find_sep_val(pars->av[pars->i]) != 1)
	{
		if (ft_find_sep_val(pars->av[pars->i]) > 1)
			pars->i = new_val_i(pars, pars->i);
		// if (ft_find_sep_val(pars->av[pars->i]) == 1)
		// 	pars->i++;
		// while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
		// 	pars->i++;
		pars->i++;
	}
}

char	**get_cmd_line(s_pars *pars)
{
	char	**ret;
	int		r;
	int		len;
	
	printf("pars->av[pars->i] = %c[%d]\n", pars->av[pars->i], pars->i);
	if (ft_find_sep_val(pars->av[pars->i]) == 1)
		pars->i++;
	while (pars->av[pars->i] && is_whitespace(pars->av[pars->i]))
		pars->i++;
	len = len_for_malloc_tab(pars);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	r = 0;
	while (pars->av[pars->i]
		&& ft_find_sep_val(pars->av[pars->i]) != 1 && len)
	{
		ret[r] = fill_cmd_line(pars);
		printf("         cmd->line[i] = %s[%d]\n", ret[r], r);
		r++;
		len--;
	}
	new_val_pars_i(pars);
	ret[r] = NULL;
	return (ret);
}