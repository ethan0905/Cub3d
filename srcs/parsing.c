/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:52:58 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 19:12:37 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parsing(t_data *data, char *file)
{
	char	*tmp;

	if (init_wall(data))
		return (1);
	if (parse_wall(data, file))
		return (1);
	if (!data->w->no.img || !data->w->so.img || !data->w->we.img
		|| !data->w->ea.img || data->f.color < 0 || data->s.color < 0)
		return (error_file(6));
	data->screen.img = mlx_new_image(data->mlx, 720, 720);
	tmp = mlx_get_data_addr(data->screen.img, &data->screen.pixel,
			&data->screen.line, &data->screen.endian);
	data->screen.addr = (int *)tmp;
	convert_img_to_int(data);
	if (parse_map(data, file))
		return (1);
	return (0);
}

int	init_wall(t_data *data)
{
	data->w = (t_wall *)ft_calloc(sizeof(t_wall), 1);
	if (!data->w)
		return (1);
	data->w->no.img = NULL;
	data->w->so.img = NULL;
	data->w->we.img = NULL;
	data->w->ea.img = NULL;
	data->screen.img = NULL;
	data->size_screen = 420;
	data->mini_map.ground = NULL;
	data->mini_map.wall = NULL;
	data->mini_map.pl = NULL;
	data->f.color = -1;
	data->s.color = -1;
	data->size = 64;
	data->h = 0;
	data->l = 0;
	data->map = 0;
	data->pl = 0;
	return (0);
}

int	init_map(t_data *data)
{
	int	i;

	data->map = (char **)ft_calloc(sizeof(char *), (data->h + 1));
	if (!data->map)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	i = 0;
	while (i < data->h)
	{
		data->map[i] = (char *)ft_calloc(sizeof(char), (data->l + 1));
		if (!data->map[i])
		{
			ft_putstr_fd("Malloc failed\n", 2);
			ft_free_ls(data->map);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_player(t_data *data)
{
	data->pl = ft_calloc(sizeof(t_player), 1);
	if (!data->pl)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		return (1);
	}
	data->pl->px = 0;
	data->pl->py = 0;
	data->pl->pdx = 0;
	data->pl->pdy = 0;
	data->pl->pa = 0;
	return (0);
}

void	convert_img_to_int(t_data *data)
{
	char	*tmp;

	tmp = mlx_get_data_addr(data->w->no.img, &data->w->no.pixel,
			&data->w->no.line, &data->w->no.endian);
	data->w->no.addr = (int *)tmp;
	tmp = mlx_get_data_addr(data->w->so.img, &data->w->so.pixel,
			&data->w->so.line, &data->w->so.endian);
	data->w->so.addr = (int *)tmp;
	tmp = mlx_get_data_addr(data->w->we.img, &data->w->we.pixel,
			&data->w->we.line, &data->w->we.endian);
	data->w->we.addr = (int *)tmp;
	tmp = mlx_get_data_addr(data->w->ea.img, &data->w->ea.pixel,
			&data->w->ea.line, &data->w->ea.endian);
	data->w->ea.addr = (int *)tmp;
}
