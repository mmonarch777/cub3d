/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:43:09 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 05:43:11 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parsing_texture(t_cub	*cub, char *line)
{
	int	num;

	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			num = 0;
		else if (ft_strncmp(line, "SO ", 3) == 0)
			num = 1;
		else if (ft_strncmp(line, "EA ", 3) == 0)
			num = 2;
		else
			num = 3;
		cub->data->texture_path[num] = ft_strdup(line + 3);
		if (cub->data->texture_path[num] == NULL
			|| ft_strlen(cub->data->texture_path[num]) == 0)
			its_error("Invalid texture path");
		return (1);
	}
	return (0);
}

int	add_map(t_cub *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '1')
		its_error("Invalid argument");
	else
		parsing_map(cub, line);
	return (1);
}

void	parsing_line(t_cub *cub, char *line)
{
	int	i;

	if (cub->data->map != NULL)
		parsing_map(cub, line);
	else
	{
		i = 0;
		while (line[i])
		{
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			if (parsing_texture(cub, line + i))
				break ;
			else if (parsing_color(cub, line + i))
				break ;
			else if (add_map(cub, line))
				break ;
		}
	}
}

void	parsing_file(char *file, t_cub *cub)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		its_error("Invalid fd");
	cub->data->color_ceil = -1;
	cub->data->color_floor = -1;
	cub->data->map = NULL;
	cub->data->texture_path = (char **)malloc(sizeof (char *) * 4);
	ret = 1;
	while (ret != 0)
	{
		line = NULL;
		ret = get_next_line(fd, &line);
		printf("%s\n", line);
		if (ret == -1)
			its_error("Invalid file\n");
		parsing_line(cub, line);
		free(line);
	}
	close(fd);
	if (cub->data->map == NULL)
		its_error("Invalid file\n");
}
