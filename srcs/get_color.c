#include "../includes/cub3d.h"

int	get_red(t_data *data, char *line, int f_or_s)
{
	int	r;

	r = ft_atoi(line);
	if (f_or_s == 0)
		data->floor.r = r;
	else if (f_or_s == 1)
		data->sky.r = r;
	// printf("line DANS RED = [%s]\n", line);
	// printf("RED = [%d]\n", data->floor.r);
	if (r >= 256)
		return (-2);
	return (r);
}

int	get_green(t_data *data, char *line, int f_or_s)
{
	int	g;

	// if (*(line + 1))
	line++;
	g = ft_atoi(line);
	if (f_or_s == 0)
		data->floor.g = g;
	else if (f_or_s == 1)
		data->sky.g = g;
	line--;
	// printf("line DANS GREEN = [%s]\n", line);
	// printf("GREEN = [%d]\n", g);
	if (g >= 256)
		return (-2);
	return (g);
}

int	get_blue(t_data *data, char *line, int f_or_s)
{
	int	b;

	line++;
	b = ft_atoi(line);
	if (f_or_s == 0)
		data->floor.b = b;
	else if (f_or_s == 1)
		data->sky.b = b;
	line--;
	// printf("line DANS BLUE = [%s]\n", line);
	// printf("BLUE = [%d]\n", b);
	if (b >= 256)
		return (-2);
	return (b);
}
