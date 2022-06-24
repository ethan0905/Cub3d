/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esafar <esafar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 18:37:43 by esafar            #+#    #+#             */
/*   Updated: 2022/06/24 18:37:44 by esafar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_new_line(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_read_file(int fd, char *buf, char *tmp)
{
	long int	rd;

	rd = read(fd, buf, 1);
	if (rd == 0)
	{
		free(tmp);
		return (NULL);
	}
	buf[rd] = 0;
	while ((check_new_line(buf) == -1) && rd > 0)
	{
		tmp = ft_strjoin_and_free_s1(tmp, buf);
		if (!tmp)
			return (NULL);
		rd = read(fd, buf, 1);
		buf[rd] = 0;
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*tmp;
	char		buf[2];

	if ((read(fd, buf, 0) == -1))
		return (NULL);
	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	tmp = ft_read_file(fd, buf, tmp);
	if (!tmp)
		return (NULL);
	return (tmp);
}
