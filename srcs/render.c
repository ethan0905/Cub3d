/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:41:39 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 18:49:32 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *print, int x, int y, int color)
{
	int	*dst;

	dst = print->addr + (y * 720 + x);
	*(int *)dst = color;
}

void	draw_vertical_line(t_data *data, float dist, t_3d_dist s, int *img)
{
	t_3d_draw	g;

	draw_vertical_line_init(data, &g, dist);
	while (g.y < data->size_screen)
	{
		if (g.y < g.line_o)
			my_mlx_pixel_put(&data->screen, s.r, g.y, data->sky.color);
		else if (g.y > g.line_o && g.y <= g.line_o + g.line_h)
		{	
			my_mlx_pixel_put(&data->screen, s.r, g.y,
				(int) img[(int)g.ty * data->size + (int) s.tx]);
			g.ty += g.ty_step;
		}
		else
			my_mlx_pixel_put(&data->screen, s.r, g.y, data->floor.color);
		g.y++;
	}
}

void	dist(t_data *data, float ra, int r)
{
	t_3d_dist	g;
	float		disth;
	float		distv;

	g.r = r;
	g.ca = data->pl->pa - ra;
	if (g.ca < 0)
		g.ca += 2 * PI;
	if (g.ca > 2 * PI)
		g.ca -= 2 * PI;
	disth = check_x_rays(data, data->pl, ra, &g.vh);
	distv = check_y_rays(data, data->pl, ra, &g.vv);
	g.ra = ra;
	if (disth < 0)
		dist_y(data, distv * cos(g.ca), g);
	else if (distv < 0)
		dist_x(data, disth * cos(g.ca), g);
	else if (distv > disth)
		dist_x(data, disth * cos(g.ca), g);
	else
		dist_y(data, distv * cos(g.ca), g);
}

void	render(t_data *data)
{
	float	ra;
	int		r;

	ra = data->pl->pa - DR * 30;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra -= 2 * PI;
	r = 0;
	while (r < 720)
	{
		dist(data, ra, r);
		ra = ra + DR / 12;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, -1, -1);
}
