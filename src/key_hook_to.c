/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_to.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:42:58 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 10:21:20 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	turn_left(t_data *data)
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

void	turn_right(t_data *data)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = data->dirx;
	data->dirx = data->dirx * cos(data->rotspeed)
		- data->diry * sin(data->rotspeed);
	data->diry = old_dirx * sin(data->rotspeed)
		+ data->diry * cos(data->rotspeed);
	old_planex = data->planex;
	data->planex = data->planex * cos(data->rotspeed)
		- data->planey * sin(data->rotspeed);
	data->planey = old_planex * sin(data->rotspeed)
		+ data->planey * cos(data->rotspeed);
}

void	make_turn(int key, t_cub *cub)
{
	if (cub->player.symbol == 'N' || cub->player.symbol == 'S')
	{
		if (key == 123)
			turn_left(cub->data);
		if (key == 124)
			turn_right(cub->data);
	}
	else
	{
		if (key == 124)
			turn_left(cub->data);
		if (key == 123)
			turn_right(cub->data);
	}
}

int	close_window(int key)
{
	if (key)
		ft_putendl_fd("EXIT", 1);
	exit(0);
}
