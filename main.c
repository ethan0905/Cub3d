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
#define P2 PI/2
#define P3 3*PI/2


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

int draw_line(t_test *test, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		my_mlx_pixel_put(&test->data, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}


// void	drw_ln(t_utils *mlx_ut, t_point start, t_point end)
// {
// 	t_color		*first;
// 	int			line;
// 	t_bresenham	value;

// 	bresenham_init(mlx_ut, &value, start, end);
// 	first = mlx_ut->color_grad;
// 	line = choose_line_tp(mlx_ut, &value);
// 	if (line == 0 && value.dx > 0)
// 		ln_no_bre_x(mlx_ut, &value);
// 	else if (line == 0 && value.dy > 0)
// 		ln_no_bre_y(mlx_ut, &value);
// 	else if (line == -1 && value.dx >= value.dy)
// 		bresenham_x_dsc(mlx_ut, &value);
// 	else if (line == -1 && value.dy > value.dx)
// 		bresenham_y_dsc(mlx_ut, &value);
// 	else if (line == 1 && value.dx > value.dy)
// 		bresenham_x(mlx_ut, &value);
// 	else
// 		bresenham_y(mlx_ut, &value);
// 	mlx_ut->color_grad = first;
// }

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

void	drawRays3D(t_test *test)
{
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo;
	ra=pa;

	r = 0;
	while (r < 1)
	{
		//-------check horizontal lines-------
		dof=0;
		float aTan= -1/tan(ra);
		if (ra > PI)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * aTan + px;
			yo= -64;
			xo= -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx =(int)(rx)>>6;
			my =(int)(ry)>>6;
			mp = my * mapWidth + mx;
			if (mp >0 && mp < mapWidth * mapHeight && worldMap[mp] == 1)
				dof = 8;// hit wall
			else //next line
			{
				// printf("rx=[%f]et ry=[%f]\n", rx, ry);
				// fflush(stdout);
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (rx>0 && ry>0)
			draw_line(test, px+5,py+5,rx,ry,0x00ff00);
		
		//-------check vertical lines-------
		dof=0;
		float nTan= -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)px >> 6) << 6) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra>P3)
		{
			rx = (((int)px >> 6) << 6) + 64;
			ry = (px - rx) * nTan + py;
			xo= -64;
			yo= -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx =(int)(rx)>>6;
			my =(int)(ry)>>6;
			mp = my * mapWidth + mx;
			if (mp > 0 && mp < mapWidth * mapHeight && worldMap[mp] == 1)
				dof = 8;// hit wall
			else //next line
			{
				// printf("rx=[%f]et ry=[%f]\n", rx, ry);
				fflush(stdout);
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (rx>0 && ry>0)
			draw_line(test, px+5,py+5,rx,ry,0x00ff00);
		r++;
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
	draw_line(test, px + 5, py + 5, px + 5 + pdx * 5, py + 5 + pdy * 5, 0xf00020);
}

int	render(t_test *test)
{
	drawBackground(test);
	drawMap2D(test);
	drawPlayer(test);
	drawRays3D(test);
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
	px = 250;
	py = 250;
	pdx = cos(pa) *5;
	pdy = sin(pa)*5;
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

