#include "libft.h"

int	ft_lstrlen(char **ls)
{
	int	i;

	i = 0;
	if (ls)
		while (ls[i])
			i++;
	return (i);
}