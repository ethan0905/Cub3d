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
#define DR 0.0174533 // 1 degree in radians


#define mapWidth 24
#define mapHeight 24
#define mapS 16
#define screenWidth 1024
#define screenHeight 512

#define w 18
#define h 18

float px, py, pdx, pdy, pa;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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

	int pixels = sqrt(((deltaX * deltaX) + (deltaY * deltaY)));

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
			my_mlx_pixel_put(&test->data, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	drawCube(t_test *test, int startx,  int starty, int sizex, int sizey, int color)
{
	int i, j;

	i = 1;
	while (i < sizex)
	{
		j = 1;
		while (j < sizey)
		{
			my_mlx_pixel_put(&test->data, startx + i, starty + j, color);
			j++;
		}
		i++;
	}
}

void	drawMap2D(t_test *test)
{
	int i, j;
	int x, y;

	i = 0;
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
			if (worldMap[i][j] == 1)
			{
				drawCube(test, j * 16, i * 16, 16, 16, 0xffffff);
			}
			j++;
		}
		i++;
	}
}

float ft_dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx-ax) * (bx-ax) + (by-ay) * (by-ay)));
}

void	drawRays3D(t_test *test)
{
	int		mx;
	int		my;
	int 	r;
	int		dof;
	float rx, ry, ra, xo, yo, disT;

	ra=pa-DR * 30;
	if (ra<0)
		ra+=2*PI;
	if (ra>2*PI)
		ra-=2*PI;

	r = 0;
	while (r < 60)
	{
		// horizontal check
		float disH=1000000, hx=px, hy=py;
		dof = 0;
		if (ra < PI)
		{
			ry = (((int)py / 16) * 16) - 0.0001;
			rx = (py - ry) * (-1 / tan(ra)) + px;
			yo = -16;
			xo = -yo * (-1 / tan(ra));
		}
		if (ra > PI)
		{
			ry = (((int)py / 16) * 16) + 16;
			rx = (py - ry) * (-1 / tan(ra)) + px;
			yo = 16;
			xo = -yo * (-1 / tan(ra));
		}
		if (!ra || ra == PI)
		{
			rx = px;
			ry = py;
			dof = mapHeight;
		}
		while (dof < mapHeight)
		{
			mx = (int)rx / 16;
			my = (int)ry / 16;
			if ((my >= 0 && mx >= 0 && my < mapHeight && mx < mapWidth)
				&& (worldMap[my][mx] == 1))
			{
				hx=rx;
				hy=ry;
				disH=ft_dist(px, py, hx, hy, ra);
				dof=mapHeight;
				break ;
			}
				// return (ft_dist(px, py, rx, ry));
			else if (my < 0 || my < 0 || my > mapHeight || mx > mapWidth)
				dof = mapHeight;
			else
			{
				rx += xo;
				ry += yo;
				dof = dof + 1;
			}
		}

		//vertical check
		dof = 0;
		float disV=1000000, vx=px, vy=py;
		if (ra < P2 || ra > P3)
		{
			rx = (((int)px / 16) * 16) - 0.0001;
			ry = (px - rx) * (-tan(ra)) + py;
			xo = -16;
			yo = -xo * (-tan(ra));
		}
		if (ra > P2 && ra < P3)
		{
			rx = (((int)px / 16) * 16) + 16;
			ry = (px - rx) * (-tan(ra)) + py;
			xo = 16;
			yo = -xo * (-tan(ra));
		}
		if (!ra || ra == PI)
		{
			rx = px;
			ry = py;
			dof = mapWidth;
		}
		while (dof < mapWidth)
		{
			mx = (int)rx / 16;
			my = (int)ry / 16;
			if ((my >= 0 && mx >= 0 && my < mapHeight && mx < mapWidth)
				&& (worldMap[my][mx] == 1))
			{
				vx=rx;
				vy=ry;
				disV=ft_dist(px, py, vx, vy, ra); 
				// dof=mapHeight;
				dof=mapWidth;
				break ;
			}
			else if (my < 0 || my < 0 || my > mapHeight || mx > mapWidth)
				dof = mapWidth;
			else
			{
				rx += xo;
				ry += yo;
				dof = dof + 1;
			}
		}
		if (disV<disH)
		{
			rx=vx;
			ry=vy;
			disT=disV;
			draw_line(test, px+5,py+5,rx,ry,0xff0000);
		}
		else if (disH<disV)
		{
			rx=hx;
			ry=hy;
			disT=disH;
			draw_line(test, px+5,py+5,rx,ry,0xff0000);
		}
		else if (disH < 0)
			printf("BLA BLAB BLA \n\n");

		//draw 3d wall

		float ca=pa-ra;
		if (ca < 0)
			ca+=2*PI;
		if (ca>2*PI)
			ca-=2*PI;
		disT=disT*cos(ca);
		float lineH=(320*16) / disT; //line height = (size_screen * size)/disT
		// printf("lineH=%f\n", lineH);
		float lineO=160-lineH/2;	//line offset

		if (lineH>320)
			lineH=320;
		printf("H=[%f] || O = [%f] || res = [%f]\n", lineH, lineO, lineH+lineO);			
		if (lineH + lineO > 0)
			draw_line(test, r*8+530, 0, r*8+530, lineH+lineO,0xff0000);

		ra+=DR;
		if (ra < 0)
			ra+=2*PI;
		if (ra > 2*PI)
			ra-=2*PI;
		r++;
	}

}

// void	drawRays3D(t_test *test)
// {
// 	int r, mx, my, mp, dof;
// 	float rx, ry, ra, xo, yo;
// 	ra=pa;

// 	r = 0;
// 	while (r < 1)
// 	{
// 		//-------check horizontal lines-------
// 		dof=0;
// 		float aTan= -1/tan(ra);
// 		if (ra > PI)
// 		{
// 			ry = (((int)py >> 6) << 6) - 0.0001;
// 			rx = (py - ry) * aTan + px;
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra < PI)
// 		{
// 			ry = (((int)py >> 6) << 6) + 64;
// 			rx = (py - ry) * aTan + px;
// 			yo= 64;
// 			xo= -yo * aTan;
// 		}
// 		if (ra == 0 || ra == PI)
// 		{
// 			rx = px;
// 			ry = py;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx =(int)(rx)>>6;
// 			my =(int)(ry)>>6;
// 			if (my >= 0 && mx >= 0 && my < mapHeight && mx < mapWidth && worldMap[my][mx] == 1)
// 				break ;
// 			else if (my < 0 || mx < 0 || my > mapHeight || mx > mapWidth)
// 				dof = mapHeight;
// 			else //next line
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof += 1;
// 			}
// 		}
// 		if (rx > 0 && ry > 0)
// 			draw_line(test, px,py,rx,ry,0x00ff00);
		
		
// 		//-------check vertical lines-------
// 		// dof=0;
// 		// float nTan= -tan(ra);
// 		// if (ra > P2 && ra < P3)
// 		// {
// 		// 	rx = (((int)px >> 6) << 6) - 0.0001;
// 		// 	ry = (px - rx) * nTan + py;
// 		// 	xo = -64;
// 		// 	yo = -xo * nTan;
// 		// }
// 		// if (ra < P2 || ra>P3)
// 		// {
// 		// 	rx = (((int)px >> 6) << 6) + 64;
// 		// 	ry = (px - rx) * nTan + py;
// 		// 	xo= -64;
// 		// 	yo= -xo * nTan;
// 		// }
// 		// if (ra == 0 || ra == PI)
// 		// {
// 		// 	rx = px;
// 		// 	ry = py;
// 		// 	dof = 8;
// 		// }
// 		// while (dof < 8)
// 		// {
// 		// 	mx =(int)(rx)>>6;
// 		// 	my =(int)(ry)>>6;
// 		// 	mp = my * mapWidth + mx;
// 		// 	if (mp > 0 && mp < mapWidth * mapHeight && worldMap[mp] == 1)
// 		// 		dof = 8;// hit wall
// 		// 	else //next line
// 		// 	{
// 		// 		// printf("rx=[%f]et ry=[%f]\n", rx, ry);
// 		// 		fflush(stdout);
// 		// 		rx += xo;
// 		// 		ry += yo;
// 		// 		dof += 1;
// 		// 	}
// 		// }
// 		// if (rx>0 && ry>0)
// 		// 	draw_line(test, px+5,py+5,rx,ry,0x00ff00);
// 		r++;
// 	}
// }

void  drawPlayer(t_test *test)
{
	drawCube(test, px, py, 10, 10, 0xffff00);
	// draw_line(test, px + 5, py + 5, px + 5 + pdx * 5, py + 5 + pdy * 5, 0xf00020);
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

int	handle_kepyress(int keysym, t_test *test)
{
	if (keysym == ESC)
		exit(0);
	else if (keysym == W)
	{
		px-=pdx;
		py-=pdy;
	}
	else if (keysym == A)
	{
		pa -= 0.03;
		if (pa < 0)
		{
			pa+=2*PI;
		}
		pdx=cos(pa) *5;
		pdy=sin(pa) *5;
	}
	else if (keysym == S)
	{	
		px+=pdx;
		py+=pdy;
	}
	else if (keysym == D)
	{
		pa += 0.03;
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
	mlx_hook(test.win, 2, 1L << 0, &handle_kepyress, &test);
	mlx_loop_hook(test.mlx, render, &test);
	mlx_hook(test.win, 17, 1L << 0, &close_win_cross, &test);
	mlx_loop(test.mlx);
	return (0);
}

