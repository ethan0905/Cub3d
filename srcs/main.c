/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:32:28 by esafar            #+#    #+#             */
/*   Updated: 2021/11/23 16:32:30 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (2);
	if (parsing(&data, av[1]))
	{
		exit_before_exec(&data);
		return (3);
	}
	data.win = mlx_new_window(data.mlx, 720, 420, "cub3d");
	start(data);
	end(&data);
	return (0);
}
