#include "parsing.h"

int	main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	parsing(av[1]);
	return (1);
}