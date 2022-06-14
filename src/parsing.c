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
		cub->date->texture_path[num] = ft_strdup(line + 3);
		if (cub->date->texture_path[num] == NULL || ft_strlen(cub->date->texture_path[num]) == 0)
			error_different("Invalid texture path");
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
		error_different("Invalid argument");
	else
		parsing_map(cub, line);
	return (1);
}

void	parsing_line(t_cub *cub, char *line)
{
	int	i;

	if (cub->date->map != NULL)
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

void	parsing_file(char *file, t_cub *cub)
{
	char	*line;
	int		fd;
	int 	ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_different("Invalid fd");
	cub->date->color_ceil = -1;
	cub->date->color_floor = -1;
	cub->date->map = NULL;
	cub->date->texture_path = (char **)malloc(sizeof (char *) * 4);
	ret = 1;
	while (ret != 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			error_different("File error\n");
		parsing_line(cub, line);
		free(line);
	}
}