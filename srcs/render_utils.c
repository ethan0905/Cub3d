/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:41:58 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 13:03:19 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dist_x(t_data *data, float dist, t_3d_dist g)
{
	g.tx = (int)(g.vh.rx) % data->size;
	if (g.ra > PI)
	{
		g.tx = data->size - 1 - g.tx;
		draw_vertical_line(data, dist, g, data->wall->so.addr);
	}
	else
		draw_vertical_line(data, dist, g, data->wall->no.addr);
}

void	dist_y(t_data *data, float dist, t_3d_dist g)
{
	g.tx = (int)(g.vv.ry) % data->size;
	if (g.ra < P2 || g.ra > P3)
	{
		g.tx = data->size - 1 - g.tx;
		draw_vertical_line(data, dist, g, data->wall->we.addr);
	}
	else
		draw_vertical_line(data, dist, g, data->wall->ea.addr);
}

void	draw_vertical_line_init(t_data *data, t_3d_draw *g, float dist)
{
	g->line_h = (data->size_screen * data->size) / dist;
	g->ty_step = data->size / g->line_h;
	g->ty_off = 0;
	if (g->line_h > data->size_screen)
	{
		g->ty_off = (g->line_h - data->size_screen) / 2;
		g->line_h = data->size_screen;
	}
	g->line_o = data->size_screen / 2 - g->line_h / 2;
	g->ty = g->ty_off * g->ty_step;
	g->y = 0;
}
