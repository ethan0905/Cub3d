/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:52:50 by esafar            #+#    #+#             */
/*   Updated: 2022/07/13 13:57:00 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_player_info(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				if (place_player(data, i, j))
					return (1);
		}
	}
	if (!data->pl->px || !data->pl->py)
		return (error_player());
	return (0);
}

int	place_player(t_data *data, int i, int j)
{
	if (data->map[i][j] == 'N' && !data->pl->px)
		data->pl->pa = 3.1415926535 / 2;
	else if (data->map[i][j] == 'S' && !data->pl->px)
		data->pl->pa = 3 * 3.1415926535 / 2;
	else if (data->map[i][j] == 'E' && !data->pl->px)
		data->pl->pa = 3.1415926535;
	else if (data->map[i][j] == 'W' && !data->pl->px)
		data->pl->pa = 0;
	else
		return (error_file(10));
	data->pl->px = j * data->size + data->size / 2;
	data->pl->py = i * data->size + data->size / 2;
	data->pl->pdx = (cos(data->pl->pa) * MV);
	data->pl->pdy = (sin(data->pl->pa) * MV);
	return (0);
}
