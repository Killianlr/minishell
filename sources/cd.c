/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:02 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/13 15:42:19 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_oldpwd(t_bui *blts)
{
	char	*oldpwd;

	oldpwd = "OLDPWD=";
	if (!oldpwd)
		return (1);
	if (add_var_env(blts, oldpwd))
		return (1);
	return (0);
}

int	cd_set_pwd(t_bui *blts)
{
	int	i;
	int	e;
	int	pwd_exi;

	i = 0;
	e = 0;
	pwd_exi = check_var_exist(blts->env, "PWD");
	while (blts->env[i] && pwd_exi < ft_strlen_tab(blts->env) && !blts->uoldpwd)
	{
		if (!ft_strncmp("OLDPWD", blts->env[i], 6))
			e = 1;
		i++;
	}
	if (!e && !blts->uoldpwd)
	{
		if (create_oldpwd(blts))
			return (1);
	}
	if (update_env(blts))
		return (1);
	free_tab(blts->exp);
	if (set_export(blts))
		return (1);
	return (0);
}