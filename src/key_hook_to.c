#include "../include/cub3d.h"

void	turn_right(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dirx;
	data->dirx = data->dirx * cos(-data->rotspeed)
			- data->diry * sin(-data->rotspeed);
	data->diry = old_dirx * sin(-data->rotspeed)
			+ data->diry * cos(-data->rotspeed);
	old_planex = data->planex;
	data->planex = data->planex * cos(-data->rotspeed)
			- data->planey * sin(-data->rotspeed);
	data->planey = old_planex * sin(-data->rotspeed)
			+ data->planey * cos(-data->rotspeed);
}

void	turn_left(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dirx;
	data->dirx = data->dirx * cos(data->rotspeed)
				 - data->diry * sin(data->rotspeed);
	data->diry = old_dirx * sin(-data->rotspeed)
				 + data->diry * cos(-data->rotspeed);
	old_planex = data->planex;
	data->planex = data->planex * cos(data->rotspeed)
				   - data->planey * sin(-data->rotspeed);
	data->planey = old_planex * sin(-data->rotspeed)
				   + data->planey * cos(data->rotspeed);
}

int	close_window(int key)
{
	exit(key);
}