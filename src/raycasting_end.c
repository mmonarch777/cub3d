#include "../include/cub3d.h"

//void	fill_vertical(t_raycaster *ray, t_data *data, int x)
//{
//	int	texy;
//	int	color;
//	int	y;
//
//	y = -1;
//	while (++y < ray->drawstart)
//		data->window[y][x] = data->color_ceil;
//	y = ray->drawstart - 1;
//	while (++y <= ray->drawend)
//	{
//		texy = (int )ray->texpos & (TEXHEIGHT - 1);
//		ray->texpos += ray->step;
//		color = data->texture[ray->textnum][TEXHEIGHT * texy + ray->texx];
//		if (ray->side == '1')
//			color = (color >> 1) & 8355711;
//		data->window[y][x] = color;
//	}
//	while (++y < WINHEIGHT)
//		data->window[y][x] = data->color_floor;
//}

void	fill_vertical(t_raycaster *ray_c, t_data *info, int x)
{
	int	texy;
	int	color;
	int	y;

	y = -1;
	while (++y < ray_c->drawstart)
		info->window[y][x] = info->color_ceil;
	y = ray_c->drawstart - 1;
	while (++y <= ray_c->drawend)
	{
		texy = (int)ray_c->texpos & (TEXHEIGHT - 1);
		ray_c->texpos += ray_c->step;
		color = info->texture[ray_c->textnum][TEXHEIGHT * \
			texy + ray_c->texx];
		if (ray_c->side == '1')
			color = (color >> 1) & 8355711;
		info->window[y][x] = color;
	}
	while (++y < WINHEIGHT)
		info->window[y][x] = info->color_floor;
}

void	draw_window(t_data *data)
{
	int x;
	int	y;

	y = -1;
	while (++y < WINHEIGHT)
	{
		x = -1;
		while (++x < WINWIDTH)
			data->img.date[y * WINWIDTH + x] = data->window[y][x];
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img.image, 0, 0);
}