/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:09:30 by achane-l          #+#    #+#             */
/*   Updated: 2022/07/12 12:04:03 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_left_pl(char **map, int x, int y)
{
	if (x > 0 && (map[y][x - 1] == '0' || map[y][x - 1] == '1'))
		return (1);
	return (0);
}

int	check_right_pl(char **map, int x, int y)
{
	if (map[y][x + 1] == '0' || map[y][x + 1] == '1')
		return (1);
	return (0);
}

int	check_top_pl(char **map, int x, int y)
{
	if (y > 0 && (map[y - 1][x] == '0' || map[y - 1][x] == '1'))
		return (1);
	return (0);
}

int	check_bottom_pl(char **map, int x, int y)
{
	if (map[y] && (map[y + 1][x] == '0' || map[y + 1][x] == '1'))
		return (1);
	return (0);
}

int	check_player_is_in_map(t_data *data)
{
	int	x_pos_player;
	int	y_pos_player;

	y_pos_player = -1;
	while (data->map[++y_pos_player])
	{
		x_pos_player = -1;
		while (data->map[y_pos_player][++x_pos_player])
		{
			if (data->map[y_pos_player][x_pos_player] == 'S' || \
			data->map[y_pos_player][x_pos_player] == 'N' || \
			data->map[y_pos_player][x_pos_player] == 'E' || \
			data->map[y_pos_player][x_pos_player] == 'W')
				break ;
		}
		if (data->map[y_pos_player][x_pos_player] == 'S' || \
		data->map[y_pos_player][x_pos_player] == 'N' || \
		data->map[y_pos_player][x_pos_player] == 'E' || \
		data->map[y_pos_player][x_pos_player] == 'W')
			break ;
	}
	return (check_wall_around_player(data, x_pos_player, y_pos_player));
}
