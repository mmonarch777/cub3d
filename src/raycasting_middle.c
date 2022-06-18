/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_middle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:43:59 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 14:24:40 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_side_position(t_raycaster *ray, t_data *data)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (data->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - data->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (data->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - data->posy) * ray->deltadisty;
	}
}

void	get_hit(t_raycaster *ray, t_data *data)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = '0';
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = '1';
		}
		if (data->map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
	if (ray->side == '0')
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

void	get_side_texture(t_raycaster *ray)
{
	if (ray->side == '1' && ray->stepy < 0)
		ray->textnum = 0;
	else if (ray->side == '1' && ray->stepy > 0)
		ray->textnum = 1;
	else if (ray->side == '0' && ray->stepx > 0)
		ray->textnum = 2;
	else if (ray->side == '0' && ray->stepx < 0)
		ray->textnum = 3;
}

void	get_data_texture_after_raycasting(t_raycaster *ray, t_data *data)
{
	ray->lineheight = (int)(WINHEIGHT / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + WINHEIGHT / 2;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + WINHEIGHT / 2;
	if (ray->drawend >= WINHEIGHT)
		ray->drawend = WINHEIGHT - 1;
	get_side_texture(ray);
	if (ray->side == '0')
		ray->wallx = data->posy + ray->perpwalldist * ray->raydiry;
	else
		ray->wallx = data->posx + ray->perpwalldist * ray->raydirx;
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * (double )TEXWIDTH);
	if (ray->side == '0' && ray->raydirx > 0)
		ray->texx = TEXWIDTH - ray->texx - 1;
	if (ray->side == '1' && ray->raydiry < 0)
		ray->texx = TEXWIDTH - ray->texx - 1;
	ray->step = 1.0 * TEXHEIGHT / ray->lineheight;
	ray->texpos = (ray->drawstart - WINHEIGHT / 2
			+ ray->lineheight / 2) * ray->step;
}

int	raycaster(t_data *data)
{
	int			x;
	t_raycaster	*ray;

	ray = (t_raycaster *)malloc(sizeof (t_raycaster));
	if (ray == NULL)
		its_error("Error malloc");
	x = -1;
	while (++x < WINWIDTH)
	{
		ray->camerx = 2 * x / (double)WINWIDTH - 1;
		ray->raydirx = data->dirx + data->planex * ray->camerx;
		ray->raydiry = data->diry + data->planey * ray->camerx;
		ray->deltadistx = fabs(1 / ray->raydirx);
		ray->deltadisty = fabs(1 / ray->raydiry);
		ray->mapx = (int) data->posx;
		ray->mapy = (int) data->posy;
		get_side_position(ray, data);
		get_hit(ray, data);
		get_data_texture_after_raycasting(ray, data);
		fill_vertical(ray, data, x);
	}
	free(ray);
	print_mini_map(data);
	draw_window(data);
	return (0);
}
