#include "../include/cub3d.h"

void	next_symbol(t_date *date, t_player player)
{
	if (player.symbol == 'W')
	{
		date->dirx = -1.0;
		date->diry = 0.0;
		date->planex = 0.0;
		date->planey = 0.66;
	}
}

void	add_vector(t_date *date, t_player player)
{
	date->posx = (float )player.x + 0.1;
	date->posy = (float )player.y + 0.1;
	if (player.symbol == 'S')
	{
		date->dirx = 0.0;
		date->diry = 1.0;
		date->planex = -0.66;
		date->planey = 0.0;
	}
	else if (player.symbol == 'E')
	{
		date->dirx = 1.0;
		date->diry = 0.0;
		date->planex = 0.0;
		date->planey = -0.66;
	}
	else if (player.symbol == 'N')
	{
		date->dirx = 0.0;
		date->diry = -1.0;
		date->planex = 0.66;
		date->planey = 0.0;
	}
	else
		next_symbol(date, player);
}

void	get_img(t_date *date, int *image, char *path, t_img *img)
{
	int	x;
	int	y;

	img->image = mlx_xpm_file_to_image(date->mlx, path, &img->width,
			&img->height);
	if (!img->image)
		its_error("Invalid texture path");
	img->pixel_bits = 4;
	img->line_bytes = img->width;
	img->endian = 0;
	img->date = (int *) mlx_get_data_addr(img->image, &img->pixel_bits,
			 &img->line_bytes, &img->endian);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			image[img->width * y + x] = img->date[img->width * y + x];
	}
	mlx_destroy_image(date->mlx, img->image);
}

void	get_image(t_date *date)
{
	t_img	img;
	int 	i;

	i = -1;
	while (++i < 4)
		get_img(date, date->texture[0], date->texture_path[0], &img);

}

int	make_by_lodev(t_date *date, t_player player)
{
	int	i;

	date->mlx = mlx_init();
	add_vector(date, player);
	date->texture = malloc(sizeof (int *) * 8);
	if (date->texture == NULL)
		its_error("Malloc error");
	i = -1;
	while (++i < 4)
	{
		date->texture[i] = malloc(sizeof (int ) * (TEXHEIGHT * TEXWIDTH));
		if (date->texture[i] == NULL)
			its_error("Malloc error");
	}
	get_image(date);
	date->win = mlx_new_window(date->mlx, WINWIDTH, WINHEIGHT, "cub3D");
	date->img.image = mlx_new_image(date->mlx, WINWIDTH, WINHEIGHT);
	date->img.date = (int *) mlx_get_data_addr(date->img.image,
			&date->img.pixel_bits, &date->img.line_bytes, &date->img.height);
	mlx_loop_hook(date->mlx, &raycaster, date);
}