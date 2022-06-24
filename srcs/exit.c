#include "../includes/cub3d.h"

void	exit_before_exec(t_data *data)
{
	free_img(data);
	if (data->wall)
		free(data->wall);
	if (data->map)
		ft_free_ls(data->map);
	if (data->pl)
		free(data->pl);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}

void	free_img(t_data *data)
{
	if (data->wall->no.img)
		mlx_destroy_image(data->mlx, data->wall->no.img);
	if (data->wall->so.img)
		mlx_destroy_image(data->mlx, data->wall->so.img);
	if (data->wall->we.img)
		mlx_destroy_image(data->mlx, data->wall->we.img);
	if (data->wall->ea.img)
		mlx_destroy_image(data->mlx, data->wall->ea.img);
	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->mini_map.ground)
		mlx_destroy_image(data->mlx, data->mini_map.ground);
	if (data->mini_map.wall)
		mlx_destroy_image(data->mlx, data->mini_map.wall);
	if (data->mini_map.pl)
		mlx_destroy_image(data->mlx, data->mini_map.pl);
}

int	end(t_data *data)
{
	free_img(data);
	if (data->wall)
		free(data->wall);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	ft_free_ls(data->map);
	free(data->pl);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}
