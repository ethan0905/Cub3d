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
#include <math.h>
// #include <string>
// #include <vector>
// #include <iostream>

// #include "quickcg.h"
// using namespace QuickCG;
// ///

#include "cub3d.h"
#define PI 3.1415926535

#define mapWidth 8
#define mapHeight 8
#define mapS 64
#define screenWidth 640
#define screenHeight 480

#define w 60
#define h 60

float px, py, pdx, pdy, pa;

int worldMap[]=
{
  1,1,1,1,1,1,1,1,
  1,0,1,0,0,0,0,1,
  1,0,1,0,0,0,0,1,
  1,0,1,0,0,0,0,1,
  1,0,0,0,0,0,0,1,
  1,0,0,0,0,1,0,1,
  1,0,0,0,0,0,0,1,
  1,1,1,1,1,1,1,1,
};


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	drawBackground(t_test *test)
{
	int x, y;

	y = 0;
	while (y < 512)
	{
		x = 0;
		while (x < 1024)
		{
			my_mlx_pixel_put(&test->data, x, y, 0x808080);
			x++;
		}
		y++;
	}
}

void	drawMap2D(t_test *test)
{
	int x, y, xo, yo;
	int i, j;

	y = 0;
	while (y < mapHeight)
	{
		x = 0;
		while (x < mapWidth)
		{
			if (worldMap[y * mapWidth + x] == 1)
			{
				// printf("[1] ");
				i=1;
				while (i<w)
				{
					j = 1;
					while (j<h)
					{
						my_mlx_pixel_put(&test->data, (x * w) + i, (y * h) + j, 0xffffff);
						j++;
					}
					i++;
					// printf("i=[%d]\n", i);
				}
			}
			else
			{
				// printf("[0] ");
				i=1;
				while (i<w)
				{
					j = 1;
					while (j<h)
					{
						my_mlx_pixel_put(&test->data, (x * w) + i, (y * h) + j, 0x000000);
						j++;
					}
					i++;
				}
			}
			// xo = x * mapS;
			// yo = y * mapS;
			x++;
		}
		// printf("\n");
		y++;
	}
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
			my_mlx_pixel_put(&test->data, px + x, py + y, 0xffff00);
			y++;
		}
		x++;
	}
	x =0;
	y = 0;
	while (x< 25)
	{
		while (y< 25)
		{
			my_mlx_pixel_put(&test->data, px + x, py + y, 0xffff00);
			y++;
		}
	}
}

int	render(t_test *test)
{
	drawBackground(test);
	drawMap2D(test);
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
	{
		px+=pdx;
		py+=pdy;
	}
	else if (keysym == A)
	{
		pa -= 0.1;
		if (pa < 0)
		{
			pa+=2*PI;
		}
		pdx=cos(pa) *5;
		pdy=sin(pa) *5;
	}
	else if (keysym == S)
	{
		px-=pdx;
		py-=pdy;
	}
	else if (keysym == D)
	{
		pa += 0.1;
		if (pa > 2*PI)
		{
			pa-=2*PI;
		}
		pdx=cos(pa) *5;
		pdy=sin(pa) *5;
	}
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

