/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:52:25 by esafar            #+#    #+#             */
/*   Updated: 2022/07/13 14:06:57 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_wall(t_data *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_texture(data, line))
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	close(fd);
	return (0);
}

int	parse_texture(t_data *data, char *line)
{
	char	**tab;
	int		ret;

	tab = NULL;
	ret = 0;
	if (line)
		tab = ft_split(line, ' ');
	if (!tab)
	{
		ft_putendl_fd("Malloc failed", 2);
		return (1);
	}
	if (!tab[0] || ft_isdigit(tab[0][0]))
	{
		ft_free_ls(tab);
		return (0);
	}
	if (!tab[1])
		ret = error_file(5);
	if (ret == 0 && get_texture(data, tab))
		ret = 1;
	ft_free_ls(tab);
	return (ret);
}

int	get_texture(t_data *data, char **tab)
{
	if (!ft_strcmp(tab[0], "NO") && !data->w->no.img)
		data->w->no.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strcmp(tab[0], "SO") && !data->w->so.img)
		data->w->so.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strcmp(tab[0], "WE") && !data->w->we.img)
		data->w->we.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strcmp(tab[0], "EA") && !data->w->ea.img)
		data->w->ea.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strcmp(tab[0], "C") && data->s.color == -1)
		data->s.color = ft_atoc(ft_strtrim(tab[1], " ", "\t"));
	else if (!ft_strcmp(tab[0], "F") && data->f.color == -1)
		data->f.color = ft_atoc(ft_strtrim(tab[1], " ", "\t"));
	else
		return (error_file(5));
	if (data->s.color == -2 || data->f.color == -2)
		return (1);
	return (0);
}
