/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:43:45 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 05:43:48 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_vertical(t_raycaster *ray, t_data *data, int x)
{
	int	texy;
	int	color;
	int	y;

	y = -1;
	while (++y < ray->drawstart)
		data->window[y][x] = data->color_ceil;
	y = ray->drawstart - 1;
	while (++y <= ray->drawend)
	{
		texy = (int )ray->texpos & (TEXHEIGHT - 1);
		ray->texpos += ray->step;
		color = data->texture[ray->textnum][TEXHEIGHT * texy + ray->texx];
		if (ray->side == '1')
			color = (color >> 1) & 8355711;
		data->window[y][x] = color;
	}
	while (++y < WINHEIGHT)
		data->window[y][x] = data->color_floor;
}

void	draw_window(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WINHEIGHT)
	{
		x = -1;
		while (++x < WINWIDTH)
			data->img.data[y * WINWIDTH + x] = data->window[y][x];
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.image, 0, 0);
}
