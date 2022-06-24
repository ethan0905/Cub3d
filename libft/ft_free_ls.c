#include "libft.h"

void	ft_free_ls(char **ls)
{
	int	i;

	i = 0;
	while (ls[i])
	{
		free(ls[i]);
		i++;
	}
	if (ls)
		free(ls);
	return ;
}