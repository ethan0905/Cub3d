/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:41:51 by esafar            #+#    #+#             */
/*   Updated: 2022/06/22 15:41:52 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_utils_game_change(t_data *data, float temp_x, float temp_y)
{
	data->pl->px -= temp_x;
	data->pl->py -= temp_y;
}
