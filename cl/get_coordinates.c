#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int		ft_str_is_clear(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isblanckspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_coordinates(double	res[3], char *value)
{
	char	*coord;

	coord = value;
	res[0] = strtod(coord, &coord);
	res[1] = strtod(coord, &coord);
	res[2] = strtod(coord, &coord);
	if (!ft_str_is_clear(coord))
		fatal("invalid coordinates");
}

double	get_rayon(char *value)
{
	double	res;

	res = strtod(value, &value);
	if (!ft_str_is_clear(value))
		fatal("invalid valueinates");
	return (res);
}

double	get_hexa(char *value)
{
	double	res;

	res = strtod(value, &value);
	if (!ft_str_is_clear(value))
		fatal("invalid valueinates");
	return (res);
}
