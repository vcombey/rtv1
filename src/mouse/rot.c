/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 16:46:35 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

cl_float3	mat_mult_vect(float a[3][3], cl_float3 v)
{
	cl_float3	res;

	res.x = a[0][0] * v.x + a[0][1] * v.y + a[0][2] * v.z;
	res.y = a[1][0] * v.x + a[1][1] * v.y + a[1][2] * v.z;
	res.z = a[2][0] * v.x + a[2][1] * v.y + a[2][2] * v.z;
	return (res);
}

cl_float3 rot(cl_float3 v, float teta)
{
	float tmp;

	tmp = v.x;
	v.x = v.x * cos(teta) - v.y * sin(teta);
	v.y = tmp * sin(teta) + v.y * cos(teta);
	return (v);
}

static float	mat_mult_coef(float a[3][3], float b[3][3], int a_line, int b_col)
{
	int	i;
	float	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i][b_col];
		i++;
	}
	return (res);
}

void	mat_mult(float res[3][3], float a[3][3], float b[3][3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i][j] = mat_mult_coef(a, b, i, j);
			j++;
		}
		i++;
	}
}

static float	mat_mult_vect_coef(float a[3][3], cl_float3 b, int a_line)
{
	float	res;

	res = 0;
	res += a[a_line][0] * b.x;
	res += a[a_line][1] * b.y;
	res += a[a_line][2] * b.z;
	return (res);
}

cl_float3	mat_mult_vect_2(float a[3][3], cl_float3 x)
{
	cl_float3	res;

	res.x = mat_mult_vect_coef(a, x, 0);
	res.y = mat_mult_vect_coef(a, x, 1);
	res.z = mat_mult_vect_coef(a, x, 2);
	return (res);
}

cl_float3	calc_rotation_figure(cl_float3 ray, cl_float3 v)
{
//	v = normalize(v);
	float	mat_x[3][3] = {
		{1, 0, 0},
		{0, v.z, -v.y},
		{0, v.y, v.z},
	};
	float	mat_y[3][3] = {
		{v.z, 0, v.x},
		{0, 1, 0},
		{-v.x, 0, v.z},
	};
	float	mat_z[3][3] = {
		{v.z, -v.x, 0},
		{v.x, v.z, 0},
		{0, 0, 1},
	};
	float	res[3][3];
	mat_mult(res, mat_y, mat_x);
	ray = mat_mult_vect(res, ray);

	return (ray);
	(void)mat_y;
	(void)mat_z;
}

cl_float3	rodrigues(cl_float3 input, cl_float3 v, float teta)
{
	cl_float3	res;
	float	mat[3][3] = {
		{cos(teta) + (1 - cos(teta)) * v.x * v.x,			(1 - cos(teta)) * v.x * v.y - sin(teta) * v.z,				(1 - cos(teta)) * v.x * v.z + sin(teta) * v.y},
		{(1 - cos(teta)) * v.x * v.y - sin(teta) * v.z,		cos(teta) + (1 - cos(teta)) * v.y * v.y,					(1 - cos(teta)) * v.y * v.z - sin(teta) * v.x},
		{(1 - cos(teta)) * v.x * v.z - sin(teta) * v.y,		(1 - cos(teta)) * v.y * v.z - sin(teta) * v.x,				cos(teta) + (1 - cos(teta)) * v.z * v.z,}
	};

	res = mat_mult_vect(mat, input);

	return (res);
}

cl_float3	rot_x(cl_float3 v, float teta)
{
	float	mat[3][3] = {
		{1, 0, 0},
		{0, cos(teta), -sin(teta)},
		{0, sin(teta), cos(teta)},
	};
	return (mat_mult_vect(mat, v));
}
cl_float3	rot_y(cl_float3 v, float teta)
{
	float	mat[3][3] = {
		{cos(teta), 0, sin(teta)},
		{0, 1, 0},
		{-sin(teta), 0, cos(teta)},
	};
	return (mat_mult_vect(mat, v));
}
cl_float3	rot_z(cl_float3 v, float teta)
{
	float	mat[3][3] = {
		{cos(teta), -sin(teta), 0},
		{sin(teta), cos(teta), 0},
		{0, 0, 1},
	};
	return (mat_mult_vect(mat, v));
}

int		invert_matrix(float m[3][3], float inv_m[3][3])
{
	float	det;

	det = m[0][0] * (m[1][4%3] * m[2][8%6] - m[2][7%6] * m[1][5%3])
		- m[0][1] * (m[1][3%3] * m[2][8%6] - m[2][6%6] * m[1][5%3])
		+ m[0][2] * (m[1][3%3] * m[2][7%6] - m[2][6%6] * m[1][4%3]);
	if (fabsf(det) < 0.0005)
		return (0);
	inv_m[0][0] = m[1][4%3] * m[2][8%6] - m[1][5%3] * m[2][7%6] / det;
	inv_m[0][1] = -(m[0][1] * m[2][8%6] - m[2][7%6] * m[0][2]) / det;
	inv_m[0][2] = m[0][1] * m[1][5%3] - m[1][4%3] * m[0][2] / det;
	inv_m[1][3%3] = -(m[1][3%3] * m[2][8%6] - m[1][5%3] * m[2][6%6]) / det;
	inv_m[1][4%3] = m[0][0] * m[2][8%6] - m[2][6%6] * m[0][2] / det;
	inv_m[1][5%3] = -(m[0][0] * m[1][5%3] - m[1][3%3] * m[0][2]) / det;
	inv_m[2][6%6] = m[1][3%3] * m[2][7%6] - m[2][6%6] * m[1][4%3] / det;
	inv_m[2][7%6] = -(m[0][0] * m[2][7%6] - m[2][6%6] * m[0][1]) / det;
	inv_m[2][8%6] = m[0][0] * m[1][4%3] - m[0][1] * m[1][3%3] / det;
	return (1);
}

void	set_rotation_matrix(float m[3][3], cl_float3 vx, cl_float3 vy, cl_float3 vz)
{
	m[0][0] = vx.x;
	m[0][1] = vy.x;
	m[0][2] = vz.x;
	m[1][0] = vx.y;
	m[1][1] = vy.y;
	m[1][2] = vz.y;
	m[2][0] = vx.z;
	m[2][1] = vy.z;
	m[2][2] = vz.z;
}

