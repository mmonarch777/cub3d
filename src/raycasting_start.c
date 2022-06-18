/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:44:08 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 13:14:20 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	next_symbol(t_data *data, t_player player)
{
	if (player.symbol == 'W')
	{
		data->dirx = -1.0;
		data->diry = 0.0;
		data->planex = 0.0;
		data->planey = 0.66;
	}
}

void	add_vector(t_data *data, t_player player)
{
	data->posx = (double )player.x + 0.5;
	data->posy = (double )player.y + 0.5;
	if (player.symbol == 'S')
	{
		data->dirx = 0.0;
		data->diry = 1.0;
		data->planex = -0.66;
		data->planey = 0.0;
	}
	else if (player.symbol == 'E')
	{
		data->dirx = 1.0;
		data->diry = 0.0;
		data->planex = 0.0;
		data->planey = -0.66;
	}
	else if (player.symbol == 'N')
	{
		data->dirx = 0.0;
		data->diry = -1.0;
		data->planex = 0.66;
		data->planey = 0.0;
	}
	else
		next_symbol(data, player);
}

void	get_img(t_data *data, int *image, char *path, t_img *img)
{
	int	x;
	int	y;

	img->image = mlx_xpm_file_to_image(data->mlx, path, &img->width,
			&img->height);
	if (!img->image)
		its_error("Invalid texture path");
	img->pixel_bits = 4;
	img->line_bytes = img->width;
	img->endian = 0;
	img->data = (int *) mlx_get_data_addr(img->image, &img->pixel_bits,
			&img->line_bytes, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			image[img->width * y + x] = img->data[img->width * y + x];
	}
	mlx_destroy_image(data->mlx, img->image);
}

void	get_image(t_data *data)
{
	t_img	img;
	int		i;

	i = -1;
	while (++i < 4)
		get_img(data, data->texture[i], data->texture_path[i], &img);
}

int	make_by_lodev(t_cub *cub, t_data *data, t_player player)
{
	int	i;

	data->mlx = mlx_init();
	add_vector(data, player);
	data->texture = malloc(sizeof (int *) * 4);
	if (data->texture == NULL)
		its_error("Malloc error");
	i = -1;
	while (++i < 4)
	{
		data->texture[i] = (int *)malloc(sizeof(int) * (TEXHEIGHT * TEXWIDTH));
		if (data->texture[i] == NULL)
			its_error("Malloc error");
	}
	get_image(data);
	data->win = mlx_new_window(data->mlx, WINWIDTH, WINHEIGHT, "cub3D");
	data->img.image = mlx_new_image(data->mlx, WINWIDTH, WINHEIGHT);
	data->img.data = (int *) mlx_get_data_addr(data->img.image,
			&data->img.pixel_bits, &data->img.line_bytes, &data->img.height);
	mlx_loop_hook(data->mlx, &raycaster, data);
	mlx_hook(cub->data->win, 2, 0, key, cub);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop(data->mlx);
	return (0);
}
