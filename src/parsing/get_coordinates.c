/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 21:44:03 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int			ft_str_is_clear(char *str)
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

cl_float3	get_coordinates(cl_float3 res, char *value)
{
	char	*coord;

	coord = value;
	if (!(ft_strtof(coord, &coord, &res.x)))
		fatal("invalid coordinates");
	if (!(ft_strtof(coord, &coord, &res.y)))
		fatal("invalid coordinates");
	if (!(ft_strtof(coord, &coord, &res.z)))
		fatal("invalid coordinates");
	if (!ft_str_is_clear(coord))
		fatal("invalid coordinates");
	return (res);
}

double		get_rayon(char *value)
{
	double	res;

	res = strtof(value, &value);
	if (!ft_str_is_clear(value))
		fatal("invalid rayon");
	return (res);
}

double		get_hexa(char *value)
{
	double	res;

	res = strtof(value, &value);
	if (!ft_str_is_clear(value))
		fatal("invalid hexadecimal value");
	return (res);
}
