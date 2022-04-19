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

#include "cub3d.h"

int	render(t_test *test)
{
	test->frame++;
	if (test->frame % 40 / 32 == 1)
		test->frame = 0;
	return (0);
}

int	close_win_cross(t_test *test)
{
	mlx_loop_end (test->mlx);
//	clean_exit(test);
	return (0);
}

int	handle_keypress(int keysym, t_test *test)
{
	if (keysym == ESC)
		exit(0);
	else if (keysym != ESC)
		write(1, &keysym, 1);
}

int	main(int ac, char **av)
{
	t_test	test;

//	get_map(&test, ac, av);
	test.mlx = mlx_init();
	test.win = mlx_new_window(test.mlx, 250, 250, "cub3d");
	test.data.img = mlx_new_image(test.mlx, 250, 250);
	test.data.addr = mlx_get_data_addr(test.data.img, &test.data.bits_per_pixel, &test.data.line_length, &test.data.endian);
	// get_all_images_and_addresses(&test);
	mlx_hook(test.win, 2, 1L << 0, &handle_keypress, &test);
	mlx_loop_hook(test.mlx, render, &test);
	mlx_hook(test.win, 17, 1L << 0, &close_win_cross, &test);
	mlx_loop(test.mlx);
	return (0);
}
