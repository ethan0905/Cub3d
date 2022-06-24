/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:48:30 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 18:48:41 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
	tab = NULL;
	return (1);
}

int	checkint(char *nb)
{
	char	*int_extremum;
	int		i;

	i = 0;
	if (nb[0] == '-')
	{
		int_extremum = "-2147483648";
		i = 1;
	}
	else
		int_extremum = "2147483647";
	if (ft_strlen(nb) >= ft_strlen(int_extremum))
	{
		while (nb[i])
		{
			if (nb[i] > int_extremum[i] || !ft_isdigit(nb[i]))
				return (0);
			++i;
		}
		return (1);
	}
	else
		return (1);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

int	ft_atoc(char *str)
{
	char	**tab;
	int		i;
	int		r;
	int		g;
	int		b;

	tab = ft_split(str, ',');
	free(str);
	if (tab == NULL)
		return (-1);
	i = 0;
	while (tab[i])
	{
		if (checkint(tab[i]) == 0 || str_is_digit(tab[i]) == 0
			|| ft_atoi(tab[i]) > 255 || ft_atoi(tab[i]) < 0)
			return (-1 * free_split(tab));
		++i;
	}
	if (i != 3)
		return (-1 * free_split(tab));
	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	free_split(tab);
	return (r * 0x010000 + g * 0x000100 + b);
}
