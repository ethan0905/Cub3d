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
// ///
// #include <cmath>
// #include <string>
// #include <vector>
// #include <iostream>

// #include "quickcg.h"
// using namespace QuickCG;
// ///

#include "cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

float px, py;

// void	drawBackground(t_test *test)
// {
// 	int x, y;

// 	x = 0;
// 	while (x < 512)
// 	{
// 		y = 0;
// 		while (y < 1024)
// 		{
// 			mlx_pixel_put(test->mlx, test->win, px + x, py + y, 0x808080);
// 			y++;
// 		}
// 		x++;
// 	}
// }

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	*dst;

	dst = data->addr + (y * 720 + x);
	*(int *)dst = color;
}

void  drawPlayer(t_test *test)
{
	int x, y;

	x = 0;
	while (x < 10)
	{
		y = 0;
		while (y < 10)
		{
			my_mlx_pixel_put(&test->data, px + x, py + y, 0xffffff);
			y++;
		}
		x++;
	}
}

int	render(t_test *test)
{
	// drawBackground(test);
	drawPlayer(test);
	mlx_put_image_to_window(test->mlx, test->win, test->data.img, -1, -1);
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
	else if (keysym == W)
		py -= 5;
	else if (keysym == A)
		px -= 5;
	else if (keysym == S)
		py += 5;
	else if (keysym == D)
		px += 5;
	else if (keysym != ESC)
		write(1, &keysym, 1);
	render(test);
}

int	main(int ac, char **av)
{
	t_test	test;

	double posX = 22, posY = 12; //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0; //time of current frame
	double oldtime = 0; //time of previous frame

//	get_map(&test, ac, av);
	test.mlx = mlx_init();
	px = 300;
	py = 300;
	test.win = mlx_new_window(test.mlx, screenWidth, screenHeight, "cub3d");
	test.data.img = mlx_new_image(test.mlx, 1024, 512);
	test.data.addr = mlx_get_data_addr(test.data.img, &test.data.bits_per_pixel, &test.data.line_length, &test.data.endian);
	// get_all_images_and_addresses(&test);
	mlx_hook(test.win, 2, 1L << 0, &handle_keypress, &test);
	mlx_loop_hook(test.mlx, render, &test);
	mlx_hook(test.win, 17, 1L << 0, &close_win_cross, &test);
	mlx_loop(test.mlx);
	return (0);
}

