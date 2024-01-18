#include "../includes/minishell.h"

int	ms_strj_s(char *s1, char *s2, int size)
{
	int		i;
	int		y;

	if (size < 0 || !s1 || !s2)
		return (0);
	i = 0;
	while (s1[i])
		i++;
	y = 0;
	while (s2[y] && i + y < size)
	{
		s1[i + y] = s2[y];
		y++;
	}
	s1[i + y] = 0;
	free(s2);
	return (1);
}

void	ms_strjoin_free(char *s1, char *s2, int status)
{
	if (status == 1)
		free(s1);
	else if (status == 2)
		free(s2);
	else if (status == 3)
	{
		free(s1);
		free(s2);
	}
}

char	*ms_strjoin_2(char *s1, char *s2)
{
	char	*str;
	int		len_s1;
	int		len_s2;
	int		i;
	int		y;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	y = 0;
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[y])
	{
		str[i + y] = s2[y];
		y++;
	}
	str[i + y] = '\0';
	return (str);
}

char	*ms_strjoin(char *s1, char *s2, int status)
{
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	str = ms_strjoin_2(s1, s2);
	if (!str)
		return (NULL);
	ms_strjoin_free(s1, s2, status);
	return (str);
}

int	env_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		return (-1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	if (s1[i + 1] && s1[i + 1] != '=')
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ms_strcmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (-1);
	if (n != (int)ft_strlen(s2) - 1)
		return (1);
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] && s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	is_char(char c)
{
	if (!c)
		return (0);
	if (ft_find_sep_val(c))
		return (0);
	if (is_whitespace(c))
		return (0);
	if (is_quote(c))
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