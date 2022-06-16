#ifndef CUB3D_H
# define CUB3D_H
# include "../libmini/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>

# define	TEXHEIGHT		64
# define	TEXWIDTH		64
# define	WINWIDTH		640
# define	WINHEIGHT		480

typedef struct	s_player
{
	int 		x;
	int 		y;
	char		symbol;
}				t_player;

typedef struct	s_img
{
	void		*image;
	int			*date;
	char		*path;
	int 		pixel_bits;
	int 		line_bytes;
	int 		endian;
	int 		width;
	int 		height;
}				t_img;

typedef struct	s_date
{
	double 		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	int 		movespeed;
	int 		rotetion;
	void		*mlx;
	void		*win;
	char		**map;
	int 		**texture;
	char		**texture_path;
	int			color_floor;
	int			color_ceil;
	t_img		img;
}				t_date;

typedef struct 	s_cub
{
	t_date		*date;
	t_player	player;
}				t_cub;

void	parsing_file(char *file, t_cub *cub);
void	its_error(char *err);
void	parsing_map(t_cub *cub, char *line);
int		parsing_color(t_cub *cub, char *line);
void	check_map(t_cub *cub);
int		make_by_lodev(t_date *date, t_player player);

#endif