/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_x_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:43:02 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 12:43:01 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_x_axix_up(t_data *data, t_player *pl, t_check *v, float ra)
{
	v->ry = (((int)pl->py / data->size) * data->size) - 0.0001;
	v->rx = (pl->py - v->ry) * (-1 / tan(ra)) + pl->px;
	v->yo = -data->size;
	v->xo = -v->yo * (-1 / tan(ra));
}

void	check_x_axix_down(t_data *data, t_player *pl, t_check *v, float ra)
{
	v->ry = (((int)pl->py / data->size) * data->size) + data->size;
	v->rx = (pl->py - v->ry) * (-1 / tan(ra)) + pl->px;
	v->yo = data->size;
	v->xo = -v->yo * (-1 / tan(ra));
}

void	check_x_axix_l_r(t_data *data, t_player *pl, t_check *v, int *dof)
{
	v->rx = pl->px;
	v->ry = pl->py;
	*dof = data->h;
}

void	check_x_axix_next(t_check *v, int *dof)
{
	v->rx += v->xo;
	v->ry += v->yo;
	*dof = *dof + 1;
}

float	check_x_rays(t_data *data, t_player *pl, float ra, t_check *v)
{
	int		mx;
	int		my;
	int		dof;

	dof = 0;
	if (ra < PI)
		check_x_axix_up(data, pl, v, ra);
	if (ra > PI)
		check_x_axix_down(data, pl, v, ra);
	if (!ra || ra == PI)
		check_x_axix_l_r(data, pl, v, &dof);
	while (dof < data->h)
	{
		mx = (int)v->rx / data->size;
		my = (int)v->ry / data->size;
		if ((my >= 0 && mx >= 0 && my < data->h && mx < data->l)
			&& (data->map[my][mx] == '1' || data->map[my][mx] == '2'))
			return (ft_dist(pl->px, pl->py, v->rx, v->ry));
		else if (my < 0 || my < 0 || my > data->h || mx > data->l)
			dof = data->h;
		else
			check_x_axix_next(v, &dof);
	}
	return (-1);
}
