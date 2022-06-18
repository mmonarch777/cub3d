/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:44:27 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 11:01:55 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libmini/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>

# define TEXHEIGHT		64
# define TEXWIDTH		64
# define WINWIDTH		940
# define WINHEIGHT		680

typedef struct s_player
{
	int			x;
	int			y;
	char		symbol;
}				t_player;

typedef struct s_img
{
	void		*image;
	int			*data;
	char		*path;
	int			pixel_bits;
	int			line_bytes;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_data
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		movespeed;
	double		rotspeed;
	void		*mlx;
	void		*win;
	int			window[WINHEIGHT][WINWIDTH];
	char		**map;
	int			**texture;
	char		**texture_path;
	int			color_floor;
	int			color_ceil;
	int			zoom;
	t_img		img;
}				t_data;

typedef struct s_raycaster
{
	double		camerx;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	double		perpwalldist;
	int			drawstart;
	int			drawend;
	int			textnum;
	double		wallx;
	int			texx;
	double		step;
	double		texpos;
}				t_raycaster;

typedef struct s_cub
{
	t_data		*data;
	t_player	player;
	t_raycaster	*raycasting;
}				t_cub;

void	parsing_file(char *file, t_cub *cub);
void	its_error(char *err);
void	parsing_map(t_cub *cub, char *line);
int		parsing_color(t_cub *cub, char *line);
void	check_map(t_cub *cub);
int		make_by_lodev(t_cub *cub, t_data *date, t_player player);
int		raycaster(t_data *date);
void	fill_vertical(t_raycaster *ray, t_data *data, int x);
void	draw_window(t_data *data);
int		key(int key, t_cub *cub);
void	make_turn(int key, t_cub *cub);
void	turn_right(t_data *data);
void	turn_left(t_data *data);
int		close_window(int key);
void	print_mini_map(t_data *data);

#endif
