/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:41:47 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 18:53:46 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(int nb, t_player *player)
{
	if (nb == 1)
	{
		player->pa -= 0.1;
		if (player->pa < 0)
			player->pa += 2 * PI;
	}
	else
	{
		player->pa += 0.1;
		if (player->pa > 2 * PI)
			player->pa -= 2 * PI;
	}
	player->pdx = (cos(player->pa) * MV);
	player->pdy = (sin(player->pa) * MV);
}

void	move_leftright(t_data *data, int nb, t_player *player)
{
	float	temp_a;
	float	temp_x;
	float	temp_y;

	if (nb > 0)
	{
		temp_a = player->pa + PI / 2;
		if (temp_a > 2 * PI)
			temp_a -= 2 * PI;
		temp_x = cos(temp_a) * MV;
		temp_y = sin(temp_a) * MV;
		if (!check_move(data, player, temp_x, temp_y))
			ft_utils_game_change(data, temp_x, temp_y);
	}
	else
	{
		temp_a = player->pa - PI / 2;
		if (temp_a < 0)
			temp_a += 2 * PI;
		temp_x = cos(temp_a) * MV;
		temp_y = sin(temp_a) * MV;
		if (!check_move(data, player, temp_x, temp_y))
			ft_utils_game_change(data, temp_x, temp_y);
	}
}

void	move_frontback(t_data *data, int nb, t_player *player)
{
	if (nb > 0)
	{
		if (!check_move_2(data, player))
		{
			player->px += player->pdx;
			player->py += player->pdy;
		}
	}
	else
	{
		if (!check_move(data, player, player->pdx, player->pdy))
		{
			player->px -= player->pdx;
			player->py -= player->pdy;
		}
	}
}

int	handle_keypress(int key, t_data *data)
{
	if (key == ESC)
		end(data);
	if (key == LEFT_ARROW)
		rotate(1, data->pl);
	if (key == RIGHT_ARROW)
		rotate(-1, data->pl);
	if (key == W)
		move_frontback(data, -1, data->pl);
	if (key == A)
		move_leftright(data, -1, data->pl);
	if (key == S)
		move_frontback(data, 1, data->pl);
	if (key == D)
		move_leftright(data, 1, data->pl);
	if (key == ESC || key == LEFT_ARROW || key == RIGHT_ARROW || key == W
		|| key == A || key == S || key == D)
		render(data);
	return (0);
}

int	start(t_data data)
{
	render(&data);
	mlx_hook(data.win, 02, (1L << 0), handle_keypress, &data);
	mlx_hook(data.win, 33, 1L << 5, end, &data);
	mlx_loop(data.mlx);
	return (0);
}
