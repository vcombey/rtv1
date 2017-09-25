/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coordinates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/25 14:35:17 by vcombey          ###   ########.fr       */
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

int		ft_strtof(char *str, char **end_ptr, float *res)
{
	float r;
	int i;
	int neg;

	r = 0;
	i = 0;
	neg = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
		if (!(ft_isdigit(str[i])))
			return (0);
	while (str[i] && ft_isdigit(str[i]))
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		float	dec_exp;
		dec_exp = 1;
		while (str[i] && ft_isdigit(str[i]))
		{
			dec_exp = dec_exp / 10;
			r += (str[i] - '0') * dec_exp;
			i++;
		}
	}
	*end_ptr = str + i;
	*res = r * neg;
	return (1);
}

cl_float3	get_coordinates(cl_float3	res, char *value)
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
