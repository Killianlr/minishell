/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:46 by kle-rest          #+#    #+#             */
/*   Updated: 2023/12/15 14:29:17 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *src, int size)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int	clear_string(t_prompt *prpt)
{
	int		start;
	int		end;
	int		i_start;
	int		i_end;

	start = 0;
	end = ft_strlen(prpt->inpt) - 1;
	i_start = 0;
	i_end = 0;
	prpt->str = NULL;
	if (!prpt->inpt)
	{
		printf("exit");
		free(prpt->inpt);
		return (1);
	}
	while (prpt->inpt[start] && (!ft_isprint(prpt->inpt[start])
			|| prpt->inpt[start] == 32) && start <= end)
		start++;
	if ((size_t)start >= ft_strlen(prpt->inpt))
		return (2);
	while (prpt->inpt[end] && (!ft_isprint(prpt->inpt[end])
			|| prpt->inpt[end] == 32))
		end--;
	i_start = ft_strlen(prpt->inpt) - start;
	i_end = ft_strlen(prpt->inpt) - (end + 1);
	prpt->str = ft_strndup(&prpt->inpt[start], i_start - i_end);
	return (0);
}

char	*pre_prompt(void)
{
	char		*pre_prompt;
	char		*user;

	user = NULL;
	if (!getenv("USER"))
	{
		pre_prompt = ft_strdup("\033[92mminishell>\033[0m ");
		if (!pre_prompt)
			return ("");
	}
	else
	{
		user = getenv("USER");
		pre_prompt = ft_strjoin("\033[93m", user);
		if (!pre_prompt)
			return ("");
		pre_prompt = ft_strjoin_fs1(pre_prompt, "\033[92m-minishell>\033[0m ");
		if (!pre_prompt)
		{
			free(pre_prompt);
			return ("");
		}
	}
	return (pre_prompt);
}

char	*ft_prompt(void)
{
	t_prompt	prpt;
	char		*prompt;
	int			i;

	prpt.inpt = NULL;
	prompt = pre_prompt();
	prpt.inpt = readline(prompt);
	free(prompt);
	i = clear_string(&prpt);
	if (i == 1)
	{
		free(prpt.inpt);
		return (NULL);
	}
	else if (i == 2)
	{
		free(prpt.inpt);
		return (ft_strdup(" "));
	}
	add_history(prpt.inpt);
	free(prpt.inpt);
	return (prpt.str);
}
