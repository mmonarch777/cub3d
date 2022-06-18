/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:43:19 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 05:43:21 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mini_putnbr(const char *str, int *i)
{
	int	number;

	number = 0;
	while (ft_isdigit(*str))
	{
		number = number * 10 + (*str - '0');
		str++;
		++(*i);
	}
	return (number);
}

int	get_number(char *line, int *i)
{
	int	number;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (!ft_isdigit(line[*i]) || (line[*i] == '0' && ft_isdigit(line[*i + 1])))
		its_error("Invalid color");
	number = mini_putnbr(line + *i, i);
	if (number > 255)
		its_error("Invalid color");
	while ((line[*i] == ' ' || line[*i] == '\t') && line[*i] != '\0')
		(*i)++;
	if (line[*i] == ',')
		++(*i);
	return (number);
}

int	get_color(char *line)
{
	int	r_g_b;
	int	i;
	int	number;
	int	count;

	i = 0;
	count = 4;
	r_g_b = 0;
	while (--count)
	{
		number = get_number(line, &i);
		r_g_b = (r_g_b << 8) + number;
	}
	if (line[i] != '\0')
		its_error("Invalid color");
	return (r_g_b);
}

int	parsing_color(t_cub *cub, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
			cub->data->color_floor = get_color(line + 2);
		else
			cub->data->color_ceil = get_color(line + 2);
		return (1);
	}
	return (0);
}
