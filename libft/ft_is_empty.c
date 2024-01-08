#include "libft.h"

int	ft_is_empty(char *str)
{
    int len;
    int i;

    if (!str)
        return(1);
    i = 0;
    len = ft_strlen(str);
    if (len == 0)
        return (1);
    while (i < len)
    {
        if (str[i] > 32 && str[i] < 127)
            return (0);
        i++;
    }
    return (1);
}
