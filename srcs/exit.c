/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:49:06 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 19:09:32 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	exit_before_exec(t_data *data)
{
	free_img(data);
	if (data->w)
		free(data->w);
	if (data->map)
		ft_free_ls(data->map);
	if (data->pl)
		free(data->pl);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_img(t_data *data)
{
	if (data->w->no.img)
		mlx_destroy_image(data->mlx, data->w->no.img);
	if (data->w->so.img)
		mlx_destroy_image(data->mlx, data->w->so.img);
	if (data->w->we.img)
		mlx_destroy_image(data->mlx, data->w->we.img);
	if (data->w->ea.img)
		mlx_destroy_image(data->mlx, data->w->ea.img);
	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->mini_map.ground)
		mlx_destroy_image(data->mlx, data->mini_map.ground);
	if (data->mini_map.wall)
		mlx_destroy_image(data->mlx, data->mini_map.wall);
	if (data->mini_map.pl)
		mlx_destroy_image(data->mlx, data->mini_map.pl);
}

int	end(t_data *data)
{
	free_img(data);
	if (data->w)
		free(data->w);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	ft_free_ls(data->map);
	free(data->pl);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
