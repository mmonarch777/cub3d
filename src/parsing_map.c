#include "../include/cub3d.h"

void	parsing_map(t_cub *cub, char *line)
{
	int		i;
	char	**mass;

	i = 0;
	if (cub->date->map != NULL)
	{
		while (cub->date->map[i])
			i++;
		mass = (char **)malloc(sizeof(char *) * i + 2);
		if (!mass)
			error_different("Error malloc map");
		mass[i + 1] = NULL;
		mass[i] = ft_strdup(line);
		if (!mass[i])
			error_different("Error malloc map");
		while (i-- > 0)
			mass[i] = cub->date->map[i];
		free(cub->date->map);
		cub->date->map = mass;
		return ;
	}
	cub->date->map = (char **)malloc(sizeof(char *) * 2);
	cub->date->map[0] = ft_strdup(line);
	cub->date->map[1] = NULL;
}