#include "../include/cub3d.h"

int	main(int arc, char **arv)
{
	t_cub *cub;

	if (arc != 2)
		error_different("Invalid argument");
	cub = (t_cub *)malloc(sizeof (t_cub));
	if (!cub)
		error_different("Error malloc");
	cub->date = (t_date *) malloc(sizeof (t_date));
	if (!cub->date)
		error_different("Error malloc");
	cub->date->movespeed = 1;
	cub->date->rotetion = 1;
	parsirng_file(arv[1], cub);

	return (0);
}