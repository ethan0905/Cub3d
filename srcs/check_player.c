/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:09:30 by achane-l          #+#    #+#             */
/*   Updated: 2022/06/28 00:37:06 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_left_pl(char **map, int x, int y)
{
	if (x > 0 && (map[y][x - 1] == '0' || map[y][x - 1] == '1'))
		return (1);
	return (0);
}

static int	check_right_pl(char **map, int x, int y)
{
	if (map[y][x + 1] == '0' || map[y][x + 1] == '1')
		return (1);
	return (0);
}

static int	check_top_pl(char **map, int x, int y)
{
	if (y > 0 && (map[y - 1][x] == '0' || map[y - 1][x] == '1'))
		return (1);
	return (0);
}

static int	check_bottom_pl(char **map, int x, int y)
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
			if (data->map[y_pos_player][x_pos_player] == 'S')
				break ;
		}
		if (data->map[y_pos_player][x_pos_player] == 'S')
			break ;
	}
	if (check_left_pl(data->map, x_pos_player, y_pos_player) && \
	check_right_pl(data->map, x_pos_player, y_pos_player) && \
	check_top_pl(data->map, x_pos_player, y_pos_player) && \
	check_bottom_pl(data->map, x_pos_player, y_pos_player)
	)
	{
		return (0);
	}
	return (1);
	return (0);
}
