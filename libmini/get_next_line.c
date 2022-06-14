#include "libft.h"


static size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static	char	*gnl_push_to_line(char *mass)
{
	int		i;
	char	*dest;

	if (mass == NULL)
		return (0);
	i = 0;
	while (mass[i] != '\n' && mass[i])
		i++;
	dest = (char *) malloc(sizeof (char) * (i + 1));
	if (!dest)
		return (0);
	i = 0;
	while (mass[i] != '\n' && mass[i] != '\0')
	{
		dest[i] = mass[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	int	gnl_strchr(const char *s, int c)
{
	char	*mass;
	int		i;

	if (!s)
		return (0);
	mass = (char *)s;
	i = 0;
	while (mass[i] != '\0')
	{
		if (mass[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

static	char	*gnl_strjoin(const char *s1, const char *s2)
{
	char	*mass;
	size_t	i;
	size_t	nb;
	size_t	lens1;
	size_t	lens2;

	i = 0;
	nb = 0;
	lens1 = ft_strlen_gnl(s1);
	lens2 = ft_strlen_gnl(s2);
	mass = (char *) malloc((lens1 + lens1 + 1) * sizeof (char));
	if (mass == NULL)
		return (NULL);
	while (nb < lens1)
	{
		mass[nb] = s1[nb];
		nb++;
	}
	while (i < lens2)
		mass[nb++] = s2[i++];
	mass[nb] = '\0';
	return (mass);
}

static	char	*gnl_update_re(char *mass)
{
	char	*dast;
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (mass[i] != '\n' && mass[i] != '\0')
		i++;
	if (mass[i] == '\0')
	{
		free(mass);
		return (0);
	}
	dast = (char *) malloc(sizeof (char) * (ft_strlen_gnl(mass) - i) + 1);
	if (!dast)
		return (0);
	i++;
	while (mass[i] != '\0')
		dast[nb++] = mass[i++];
	dast[nb] = '\0';
	free(mass);
	return (dast);
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		*last;
	char		buf[BUFF_SIZE + 1];
	int			bwr;

	bwr = 1;
	if ((!line || fd < 0 || read(fd, 0, 0) < 0) || BUFF_SIZE <= 0)
		return (-1);
	while (!gnl_strchr(remainder, '\n') && bwr)
	{
		bwr = read(fd, buf, BUFF_SIZE);
		buf[bwr] = '\0';
		last = remainder;
		remainder = gnl_strjoin(remainder, buf);
		if (!remainder)
			return (-1);
		if (last != NULL)
			free(last);
	}
	*line = gnl_push_to_line(remainder);
	remainder = gnl_update_re(remainder);
	if (bwr == 0)
		return (0);
	return (1);
}
