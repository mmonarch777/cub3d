#include "../include/cub3d.h"

void	step_forward(t_data *data)
{
	if (ft_strchr("0", data->map[(int )(data->posy)][(int )(data->posx
		+ data->dirx * data->movespeed)]))
		data->posx += data->dirx * data->movespeed;
	if (ft_strchr("0", data->map[(int )(data->posy + data->diry
		* data->movespeed)][(int )(data->posx)]))
		data->posy += data->diry * data->movespeed;
}

void	step_back(t_data *data)
{
	if (ft_strchr("0", data->map[(int )(data->posy)][(int )(data->posx
		- data->dirx * data->movespeed)]))
		data->posx -= data->dirx * data->movespeed;
	if (ft_strchr("0", data->map[(int )(data->posy - data->diry
		* data->movespeed)][(int )(data->posx)]))
		data->posy -= data->diry * data->movespeed;
}

void	step_right(t_data *data)
{
	if (ft_strchr("0", data->map[(int )(data->posy)][(int )(data->posx
		+ data->planex * data->movespeed)]))
		data->posx += data->planex * data->movespeed;
	if (ft_strchr("0", data->map[(int )(data->posy + data->planey
		* data->movespeed)][(int )(data->posx)]))
		data->posy += data->planey * data->movespeed;
}

void	step_left(t_data *data)
{
	if (ft_strchr("0", data->map[(int )(data->posy)][(int )(data->posx
		- data->planex * data->movespeed)]))
		data->posx -= data->planex * data->movespeed;
	if (ft_strchr("0", data->map[(int )(data->posy - data->planey
		* data->movespeed)][(int )(data->posx)]))
		data->posy -= data->planey * data->movespeed;
}

int	key(int key, t_data *data)
{
	if (key == 13 || key == 126)
		step_forward(data);
	if (key == 1 || key == 125)
		step_back(data);
	if (key == 2)
		step_right(data);
	if (key == 0)
		step_left(data);
	if (key == 123)
		turn_left(data);
	if (key == 124)
		turn_right(data);
	if (key == 53)
		exit(0);
	return (0);
}