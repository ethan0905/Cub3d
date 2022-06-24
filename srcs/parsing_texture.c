/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:52:25 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 18:52:33 by esafar           ###   ########.fr       */
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
	if (!ft_strncmp(tab[0], "NO", ft_strlen(tab[0])) && !data->wall->no.img)
		data->wall->no.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strncmp(tab[0], "SO", ft_strlen(tab[0])) && !data->wall->so.img)
		data->wall->so.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strncmp(tab[0], "WE", ft_strlen(tab[0])) && !data->wall->we.img)
		data->wall->we.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strncmp(tab[0], "EA", ft_strlen(tab[0])) && !data->wall->ea.img)
		data->wall->ea.img = mlx_xpm_file_to_image(data->mlx, tab[1],
				&data->size, &data->size);
	else if (!ft_strncmp(tab[0], "C", ft_strlen(tab[0])) && data->sky.color == -1)
		data->sky.color = ft_atoc(ft_strtrim(tab[1], " ", "\t"));
	else if (!ft_strncmp(tab[0], "F", ft_strlen(tab[0])) && data->floor.color == -1)
		data->floor.color = ft_atoc(ft_strtrim(tab[1], " ", "\t"));
	else
		return (error_file(5));
	if (data->sky.color == -2 || data->floor.color == -2)
		return (1);
	return (0);
}
