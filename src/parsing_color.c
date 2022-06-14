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
		error_different("Invalid color");
	number = mini_putnbr(line + *i, i);
	if (number > 255)
		error_different("Invalid color");
	while (line[*i] == ' ' || line[*i] == '\t')
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
	count = 3;
	r_g_b = 0;
	while (--count)
	{
		number = get_number(line, &i);
		r_g_b = (r_g_b << 8) + number;
	}
	if (line[i] != '\0')
		error_different("Invalid color");
	free(line);
	return (r_g_b);
}

int parsing_color(t_cub *cub, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
	{
		if (ft_strncmp(line, "F ", 2) == 0)
			cub->date->color_floor = get_color(line + 2);
		else
			cub->date->color_ceil = get_color(line + 2);
		return (1);
	}
	return (0);
}