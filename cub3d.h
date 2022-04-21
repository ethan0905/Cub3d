/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:11:34 by esafar            #+#    #+#             */
/*   Updated: 2021/11/17 09:53:04 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./mlx/mlx.h"

# define ESC 65307
# define SPACE 32
# define W 119
# define A 97
# define S 115
# define D 100

# define BUFFER_SIZE 1
# define FRAME 250

# define ERROR -1
# define SUCCESS 1

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_data;

typedef struct s_param
{
	char	**map;
	int		width;
	int		height;
}				t_param;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
}	t_player;

typedef struct s_tex
{
	int		tex_x;
	int		tex_y;
	double	ratio_x;
	double	ratio_y;
}				t_tex;

typedef struct s_test
{
	void		*mlx;
	void		*win;
	int			loop;
	t_param		param;
	t_data		data;
	t_player	player;
	t_tex		tex;
}				t_test;

char	*get_line(char *save);
int		get_map(t_test *test, int ac, char **av);

//KEYPRESS
int		handle_keypress(int keysym, t_test *test);
void	check_game_keypress(t_test *test, int keysym);

//UTILS
int		get_pixel(t_data *img, int x, int y);
void	draw_on_image(t_test *test, t_data *img, int startx, int starty);
void	draw_on_image_bis(t_test *test, t_data *img, int startx, int starty);
void	draw_on_image_intro(t_test *test, t_data *img, int startx, int starty);

//EXIT
// void	clean_exit(t_test *test);
// int		close_win_cross(t_test *test);

#endif
