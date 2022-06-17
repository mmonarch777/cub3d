#include "../include/cub3d.h"

int	main(int arc, char **arv)
{
	t_cub *cub;

	if (arc != 2)
		its_error("Invalid argument");
	cub = (t_cub *)malloc(sizeof (t_cub));
	if (!cub)
		its_error("Error malloc");
	cub->data = (t_data *) malloc(sizeof (t_data));
	if (!cub->data)
		its_error("Error malloc");
	cub->data->movespeed = 1;
	cub->data->rotspeed = 1;
	parsing_file(arv[1], cub);
	check_map(cub);
	make_by_lodev(cub->data, cub->player);
	return (0);
}