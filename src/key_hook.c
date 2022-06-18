/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:42:46 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 10:21:20 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	step_forward(t_data *data)
{
	if (ft_strchr("0", data->map[(int )(data->posy)][(int )(data->posx
		+ data->dirx * data->movespeed)]))
		data->posx += data->dirx * data->movespeed;
	if (ft_strchr("0", data->map[(int )(data->posy
				+ data->diry * data->movespeed)][(int )(data->posx)]))
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

int	key(int key, t_cub *cub)
{
	if (key == 13 || key == 126)
		step_forward(cub->data);
	if (key == 1 || key == 125)
		step_back(cub->data);
	if (key == 2)
		step_right(cub->data);
	if (key == 0)
		step_left(cub->data);
	make_turn(key, cub);
	if (key == 53)
	{
		ft_putendl_fd("EXIT", 2);
		exit(0);
	}
	return (0);
}
