#include "../include/cub3d.h"

int	main(int arc, char **arv)
{
	t_cub *cub;

	if (arc != 2)
		its_error("Invalid argument");
	cub = (t_cub *)malloc(sizeof (t_cub));
	if (!cub)
		its_error("Error malloc");
	cub->date = (t_date *) malloc(sizeof (t_date));
	if (!cub->date)
		its_error("Error malloc");
	cub->date->movespeed = 1;
	cub->date->rotetion = 1;
	parsing_file(arv[1], cub);
	check_map(cub);
	make_by_lodev(cub->date, cub->player);
	return (0);
}