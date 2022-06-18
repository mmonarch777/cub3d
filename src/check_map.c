/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:41:45 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 06:29:52 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_all_symbols(t_cub *cub, char **map, int *y, int x)
{
	int	player;

	player = 0;
	while (map[++(*y)])
	{
		x = -1;
		while (map[*y][++x])
		{
			if (map[*y][x] != 'N' && map[*y][x] != 'E' && map[*y][x] != 'S'
				&& map[*y][x] != 'W' && map[*y][x] != ' '
				&& map[*y][x] != '0' && map[*y][x] != '1')
				its_error("Invalid symbols in the map");
			if (map[*y][x] == 'N' || map[*y][x] == 'E' || map[*y][x] == 'S'
				|| map[*y][x] == 'W')
			{
				cub->player.x = x;
				cub->player.y = *y;
				cub->player.symbol = map[*y][x];
				map[*y][x] = '0';
				player++;
			}
		}
	}
	if (player != 1)
		its_error("There must be one player on the map");
}

void	check_lower_and_upper_bounds(char **mass, int y)
{
	int	i;

	i = 0;
	while (mass[0][i] != '\0')
	{
		if (mass[0][i] == '0')
			its_error("Invalid map. Border don't closed");
		i++;
	}
	i = 0;
	while (mass[y][i] != '\0')
	{
		if (mass[0][i] == '0')
			its_error("Invalid map. Border don't closed");
		i++;
	}
}

int	check_spase(char **map, int y, int x, char s)
{
	if (map[y + 1][x] == s || !map[y + 1][x] || map[y - 1][x] == s
		|| !map[y - 1][x] || map[y][x + 1] == s || !map[y][x + 1]
		|| map[y][x - 1] == s || !map[y][x - 1])
		return (1);
	return (0);
}

void	check_other_bounds(t_cub *cub, char s)
{
	int	y;
	int	x;

	y = 1;
	while (cub->data->map[y + 1])
	{
		x = 1;
		if (cub->data->map[y][0] == s)
			its_error("Invalid map. Border don't closed");
		while (cub->data->map[y][x + 1])
		{
			if (cub->data->map[y][x] == s)
			{
				if (check_spase(cub->data->map, y, x, ' '))
					its_error("Invalid map. Border don't closed");
			}
			x++;
		}
		if (cub->data->map[y][x] == s)
			its_error("Invalid map. Border don't closed");
		y++;
	}
}

void	check_map(t_cub *cub)
{
	int	y;

	y = -1;
	check_all_symbols(cub, cub->data->map, &y, -1);
	check_lower_and_upper_bounds(cub->data->map, y - 1);
	check_other_bounds(cub, '0');
}
