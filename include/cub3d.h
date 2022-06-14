#ifndef CUB3D_H
# define CUB3D_H
# include "../libmini/libft.h"
# include "../minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>

typedef struct	s_player
{
	int 		x;
	int 		y;
	char		symbol;
}				t_player;

typedef struct	s_date
{
	int 		movespeed;
	int 		rotetion;
	char		**map;
	char		**texture_path;
	int			color_floor;
	int			color_ceil;
}				t_date;

typedef struct 	s_cub
{
	t_date		*date;
	t_player	player;
}				t_cub;

void	error_different(char *err);
void	parsing_map(t_cub *cub, char *line);
int		parsing_color(t_cub *cub, char *line);

#endif