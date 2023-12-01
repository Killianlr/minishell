
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
		exit(0);
	}
	while (prpt->inpt[start] && (!ft_isprint(prpt->inpt[start]) || prpt->inpt[start] == 32) && start <= end)
		start++;
	if ((size_t)start >= ft_strlen(prpt->inpt))
		return (1);
	while (prpt->inpt[end] && (!ft_isprint(prpt->inpt[end]) || prpt->inpt[end] == 32))
		end--;
	i_start = ft_strlen(prpt->inpt) - start;
	i_end = ft_strlen(prpt->inpt) - (end + 1);
	prpt->str = ft_strndup(&prpt->inpt[start], i_start - i_end);
	return (0);
}

char	*ft_prompt()
{
	t_prompt	prpt;
	char	*user;
	char	*prompt;

	prpt.inpt = NULL;
	user = getenv("USER");
	prompt = ft_strjoin("\033[93m", user);
	prompt = ft_strjoin_ps(prompt, "\033[92m-minishell>\033[0m ");
    prpt.inpt = readline(prompt);
	if (clear_string(&prpt))
	{
		free(prpt.inpt);
		free(prompt);
		return (NULL);
	}
    add_history(prpt.inpt);
	free(prpt.inpt);
	free(prompt);
	return (prpt.str);
}
