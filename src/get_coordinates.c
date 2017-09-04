#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int		ft_str_is_clear(char *str)
{
	size_t	i;

	while (str[i])
	{
		if (!ft_is_space(str[i]))
			return (0);
	}
	return (1);
}

void	get_coordinates(double	*res[3], char *value)
{
	char	*coord;
	size_t	i;

	coord = value;
	i = 0;
	while (i < nb)
	{	
		(*res)[i] = strtod(coord, &coord);
		i++;
	}
	if (!ft_str_is_clear(coord))
		fatal("invalid coordinates");
}

double	get_rayon(char *value)
{

}

double	get_hexa(char *value)
{
}
