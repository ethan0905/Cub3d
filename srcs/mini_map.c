/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:42:36 by esafar            #+#    #+#             */
/*   Updated: 2022/06/22 15:42:37 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	short_pitw(t_data *data, void *img, int x, int y)
{
	mlx_put_image_to_window(data->mlx, data->win, img, x, y);
}

int	create_mini(t_data *data)
{
	int	size_player;

	size_player = 5;
	data->mini_map.size_map = 32;
	data->mini_map.ground = mlx_xpm_file_to_image(data->mlx, "./textures/floor.xpm",
			&data->mini_map.size_map, &data->mini_map.size_map);
	data->mini_map.wall = mlx_xpm_file_to_image(data->mlx, "./textures/wall.xpm",
			&data->mini_map.size_map, &data->mini_map.size_map);
	data->mini_map.pl = mlx_xpm_file_to_image(data->mlx, "./textures/player.xpm",
			&size_player, &size_player);
	if (!data->mini_map.ground || !data->mini_map.wall || !data->mini_map.pl)
		return (1);
	return (0);
}

void	ft_mini_map_if(t_data *data, int y, int x)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (i < 2)
	{
		while (j < 2)
		{
			if (data->map[y + j][x + i] == '1')
				short_pitw(data, data->mini_map.wall, (i + 1) * 64, (j + 1) * 64);
			else
				short_pitw(data, data->mini_map.ground, (i + 1) * 64, (j + 1) * 64);
			j++;
		}
		j = -1;
		i++;
	}
}

void	ft_mini_map(t_data *data)
{
	int	x;
	int	y;

	y = (int)data->pl->py / 64;
	x = (int)data->pl->px / 64;
	ft_mini_map_if(data, y, x);
	mlx_put_image_to_window(data->mlx, data->win, data->mini_map.pl,
		62 + (int)data->pl->px % 64, 62 + (int)data->pl->py % 64);
}
