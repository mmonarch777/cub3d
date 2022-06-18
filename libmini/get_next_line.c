/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonarch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 05:50:01 by mmonarch          #+#    #+#             */
/*   Updated: 2022/06/18 05:50:12 by mmonarch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_reminder(char **reminder, char **line)
{
	char	*mass;

	mass = NULL;
	if (*reminder)
	{
		mass = ft_strchr(*reminder, '\n');
		if (mass)
		{
			*mass = '\0';
			*line = ft_strdup(*reminder);
			ft_strcpy(*reminder, ++mass);
			return (mass);
		}
		else
		{
			*line = ft_strdup(*reminder);
			free(*reminder);
			*reminder = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (mass);
}

int	check_rules(char **buf, int fd, char **line)
{
	if (!line || BUFF_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	*buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buf)
		return (-1);
	return (1);
}

void	get_tmp_chr(char **ptr_chr, char **reminder)
{
	**ptr_chr = '\0';
	(*ptr_chr)++;
	*reminder = ft_strdup(*ptr_chr);
}

int	get_next_line(int fd, char **line)
{
	static char	*reminder;
	int			rb;
	char		*buf;
	char		*ptr_chr;
	char		*tmp;

	rb = check_rules(&buf, fd, line);
	if (rb < 0)
		return (-1);
	ptr_chr = check_reminder(&reminder, line);
	while (!ptr_chr && rb > 0)
	{
		rb = read(fd, buf, BUFF_SIZE);
		buf[rb] = '\0';
		ptr_chr = ft_strchr(buf, '\n');
		if (ptr_chr)
			get_tmp_chr(&ptr_chr, &reminder);
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	free(buf);
	return (rb && reminder);
}
