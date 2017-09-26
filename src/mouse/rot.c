/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 17:00:31 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

cl_float3	rot(cl_float3 v, float teta)
{
	float tmp;

	tmp = v.x;
	v.x = v.x * cos(teta) - v.y * sin(teta);
	v.y = tmp * sin(teta) + v.y * cos(teta);
	return (v);
}

cl_float3	rot_x(cl_float3 v, float teta)
{
	static float	mat[3][3] = {
		{1, 0, 0},
		{0, cos(teta), -sin(teta)},
		{0, sin(teta), cos(teta)},
	};

	return (mat_mult_vect(mat, v));
}

cl_float3	rot_y(cl_float3 v, float teta)
{
	static float	mat[3][3] = {
		{cos(teta), 0, sin(teta)},
		{0, 1, 0},
		{-sin(teta), 0, cos(teta)},
	};

	return (mat_mult_vect(mat, v));
}

cl_float3	rot_z(cl_float3 v, float teta)
{
	static float	mat[3][3] = {
		{cos(teta), -sin(teta), 0},
		{sin(teta), cos(teta), 0},
		{0, 0, 1},
	};

	return (mat_mult_vect(mat, v));
}
