/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:41:51 by esafar            #+#    #+#             */
/*   Updated: 2022/07/12 12:05:23 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_utils_game_change(t_data *data, float temp_x, float temp_y)
{
	data->pl->px -= temp_x;
	data->pl->py -= temp_y;
}

int	check_wall_around_player(t_data *data, int x_pos_player, int y_pos_player)
{
	if (check_left_pl(data->map, x_pos_player, y_pos_player) && \
	check_right_pl(data->map, x_pos_player, y_pos_player) && \
	check_top_pl(data->map, x_pos_player, y_pos_player) && \
	check_bottom_pl(data->map, x_pos_player, y_pos_player))
		return (0);
	return (1);
}
