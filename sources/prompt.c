/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:18:46 by kle-rest          #+#    #+#             */
/*   Updated: 2024/01/20 15:33:36 by fserpe           ###   ########.fr       */
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

int	clear_string_next(t_prompt *prpt, int start, int end)
{
	int		i_start;
	int		i_end;

	i_start = ft_strlen(prpt->inpt) - start;
	i_end = ft_strlen(prpt->inpt) - (end + 1);
	prpt->str = ft_strndup(&prpt->inpt[start], i_start - i_end);
	if (!prpt->str)
		return (1);
	return (0);
}

int	clear_string(t_prompt *prpt, t_gc *garbage)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(prpt->inpt) - 1;
	prpt->str = NULL;
	if (!prpt->inpt)
	{
		printf("exit\n");
		free(prpt->inpt);
		free_all(garbage);
		exit(0);
	}
	while (prpt->inpt[start] && (!ft_isprint(prpt->inpt[start])
			|| prpt->inpt[start] == 32) && start <= end)
		start++;
	if ((size_t)start >= ft_strlen(prpt->inpt))
		return (1);
	while (prpt->inpt[end] && (!ft_isprint(prpt->inpt[end])
			|| prpt->inpt[end] == 32))
		end--;
	if (clear_string_next(prpt, start, end))
		return (1);
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

char	*ft_prompt(t_gc *garbage)
{
	t_prompt	prpt;
	char		*prompt;

	prpt.inpt = NULL;
	prompt = pre_prompt();
	prpt.inpt = readline(prompt);
	free(prompt);
	if (clear_string(&prpt, garbage))
	{
		free(prpt.inpt);
		return (NULL);
	}
	add_history(prpt.inpt);
	free(prpt.inpt);
	return (prpt.str);
}
