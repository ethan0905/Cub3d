#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include "../mlx/mlx_int.h"

# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2
# define MV 5
# define DR 0.0174533

# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel;
	int		line;
	int		endian;
}	t_img;

typedef struct s_wall
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_wall;

typedef struct s_player
{
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
}	t_player;

typedef struct s_mini_map
{
	void	*ground;
	void	*wall;
	void	*pl;
	int		size_map;
}	t_mini_map;

typedef struct s_check
{
	float	rx;
	float	ry;
	float	xo;
	float	yo;
}	t_check;

typedef struct s_3d_dist
{
	int		r;
	t_check	vh;
	t_check	vv;
	float	ra;
	float	ca;
	float	tx;
}	t_3d_dist;

typedef struct s_3d_draw
{
	int		y;
	float	line_h;
	float	line_o;
	float	ty;
	float	ty_off;
	float	ty_step;
}	t_3d_draw;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			h;
	int			l;
	t_img		screen;
	int			size_screen;
	t_wall		*wall;
	int			floor;
	int			sky;
	int			size;
	t_player	*pl;
	t_mini_map	mini_map;
}	t_data;

int		start(t_data d);
void	render(t_data *data);
void	draw_vertical_line(t_data *data, float dist, t_3d_dist s, int *img);
float	check_x_rays(t_data *data, t_player *pl, float ra, t_check *v);
float	check_y_rays(t_data *data, t_player *pl, float ra, t_check *v);
int		check_move(t_data *data, t_player *p, float dx, float dy);
int		check_move_2(t_data *data, t_player *p);
float	ft_dist(float x, float y, float x2, float y2);
void	dist_x(t_data *data, float dist, t_3d_dist g);
void	dist_y(t_data *data, float dist, t_3d_dist g);
void	draw_vertical_line_init(t_data *data, t_3d_draw *g, float dist);

int		handle_keypress(int key, t_data *data);
void	rotate(int nb, t_player *p);
void	move_leftright(t_data *data, int nb, t_player *p);
void	move_frontback(t_data *data, int nb, t_player *p);

int		parse_map(t_data *data, char *file);
int		get_size_map(t_data *data, char *file);
int		is_part_of_map(t_data *data, char *line);
void	get_map(t_data *data, char *line);
void	fill_map(t_data *data, char *line, int i, int j);
int		parse_wall(t_data *data, char *file);
int		parse_texture(t_data *data, char *line);
int		get_texture(t_data *data, char **tab);
int		get_color(char **line);
int		one_line(char *line);
int		check_map_closed(t_data *data);
int		check_left(t_data *data);
int		check_right(t_data *data);
int		check_top_and_bot(t_data *data);
int		ft_intlen(int nb);
int		check_args(int ac, char **av);
int		check_good_format(char *file);
int		error_file(int err);
int		error_player(void);
int		check_no_more(char *line, int i);

void	short_pitw(t_data *data, void *img, int x, int y);
int		create_mini(t_data *data);
void	ft_mini_map_if(t_data *data, int y, int x);
void	ft_mini_map(t_data *data);
// int		create_mini_bonus(t_data *data);

int		parsing(t_data *data, char *file);
int		init_wall(t_data *data);
int		init_map(t_data *data);
int		init_player(t_data *data);
void	convert_img_to_int(t_data *data);
int		get_player_info(t_data *data);
int		place_player(t_data *data, int i, int j);

void	exit_before_exec(t_data *data);
void	free_img(t_data *data);
int		end(t_data *data);

void	ft_mini_map(t_data *data);
void	print_map(t_data *data);
void	print_player(t_data *data);
void	print_texture(t_data *data);
void	print_all(t_data *data);

void	ft_utils_game_change(t_data *data, float temp_x, float temp_y);

int		get_red(char *line);
int		get_green(char *line);
int		get_blue(char *line);

#endif
