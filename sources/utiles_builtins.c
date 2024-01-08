/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:19:22 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:32:14 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(void)
{
	return (getcwd(NULL, 4096));
}

int	ft_strlen_tab(char **env)
{
	int		i;

	i = 0;
	if (!env[i])
		return (0);
	while (env && *env)
	{
		i++;
		env++;
	}
	return (i);
}

int	ft_size_var_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	update_var(t_bui *blts, char *arg, int j)
{
	free(blts->exp[j]);
	blts->exp[j] = add_db_quote(arg);
	if (!blts->exp[j])
		return (0);
	if (update_var_env(blts, arg))
		return (1);
	return (0);
}

int	check_var_exist(char **tableau, char *arg)
{
	int	i;
	int	len1;
	int	len2;

	i = 0;
	while (tableau[i])
	{
		len1 = ft_size_var_env(arg);
		len2 = ft_size_var_env(tableau[i]);
		if ((len1 - len2) == 0)
		{
			if (!ft_strncmp(arg, tableau[i], len1))
			{
				if ((int)ft_strlen(arg) > ft_size_var_env(tableau[i]))
					return (i);
				return (0);
			}
		}
		i++;
	}
	return (i + 1);
}
