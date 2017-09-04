#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	get_coordinates(double	*res[3], char *value)
{
	char	*coord;

	coord = value;
	(*res)[0] = strtod(coord, &coord);
	(*res)[1] = strtod(coord, &coord);
	(*res)[2] = strtod(coord, &coord);
}

