/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:43:10 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 13:04:54 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_wall(float x, float y, t_data *data)
{
	int	pos_x;
	int	pos_y;

	pos_x = (int)x / data->size;
	pos_y = (int)y / data->size;
	if (data->map[pos_x][pos_y] == '1')
		return (1);
	return (0);
}

int	check_radius(float x, float y, float r, t_data *data)
{
	int		i;
	int		j;
	float	tmp;

	i = (r * -1) + x + 1;
	j = (r * -1) + y + 1;
	while (i < r + x)
	{
		while (j < r + y)
		{
			tmp = sqrt(powf(x - i, 2) + powf(y - j, 2));
			if (tmp <= r)
				if (check_wall(j, i, data))
					return (1);
			j++;
		}
		j = (r * -1) + y + 1;
		i++;
	}
	return (0);
}

int	check_move(t_data *data, t_player *player, float dx, float dy)
{
	float	tx;
	float	ty;

	tx = player->px - dx;
	ty = player->py - dy;
	return (check_radius(tx, ty, 10, data));
}

int	check_move_2(t_data *data, t_player *player)
{
	float	tx;
	float	ty;

	tx = player->px + player->pdx;
	ty = player->py + player->pdy;
	return (check_radius(tx, ty, 10, data));
}
