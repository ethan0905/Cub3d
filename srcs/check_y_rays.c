/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_y_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:42:57 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 12:43:43 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_y_axix_right(t_data *data, t_player *pl, t_check *v, float ra)
{
	v->rx = (((int)pl->px / data->size) * data->size) + data->size;
	v->ry = (pl->px - v->rx) * -tan(ra) + pl->py;
	v->xo = data->size;
	v->yo = -v->xo * -tan(ra);
}

void	check_y_axix_left(t_data *data, t_player *pl, t_check *v, float ra)
{
	v->rx = (((int)pl->px / data->size) * data->size) - 0.0001;
	v->ry = (pl->px - v->rx) * -tan(ra) + pl->py;
	v->xo = -1 * data->size;
	v->yo = -v->xo * -tan(ra);
}

void	check_y_axix_up_down(t_data *data, t_player *pl, t_check *v, int *dof)
{
	v->rx = pl->px;
	v->ry = pl->py;
	*dof = data->l;
}

void	check_y_axix_next(t_check *v, int	*dof)
{
	v->rx += v->xo;
	v->ry += v->yo;
	*dof = *dof + 1;
}

float	check_y_rays(t_data *data, t_player *pl, float ra, t_check *v)
{
	int		mx;
	int		my;
	int		dof;

	dof = 0;
	if (ra < P2 || ra > P3)
		check_y_axix_left(data, pl, v, ra);
	if (ra > P2 && ra < P3)
		check_y_axix_right(data, pl, v, ra);
	if (!ra || ra == PI)
		check_y_axix_up_down(data, pl, v, &dof);
	while (dof < data->l)
	{
		mx = (int)v->rx / data->size;
		my = (int)v->ry / data->size;
		if ((my >= 0 && mx >= 0 && my < data->h && mx < data->l)
			&& (data->map[my][mx] == '1' || data->map[my][mx] == '2'))
			return (ft_dist(pl->px, pl->py, v->rx, v->ry));
		else if (my < 0 || my < 0 || my > data->h || mx > data->l)
			dof = data->l;
		else
			check_y_axix_next(v, &dof);
	}
	return (-1);
}
