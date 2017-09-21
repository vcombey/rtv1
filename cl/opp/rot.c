#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

static double	mat_mult_coef(float3 a[3], float3 b[3], size_t a_line, size_t b_col)
{
	size_t	i;
	double	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i][b_col];
		i++;
	}
	return (res);
}

void	mat_mult(float3 res[3], float3 a[3], float3 b[3])
{
	size_t	i;
	size_t	j;

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

static double	mat_mult_vect_coef(float3 a[3], float3 b, size_t a_line)
{
	size_t	i;
	double	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i];
		i++;
	}
	return (res);
}

void	mat_mult_vect(float3 res, float3 a[3], float3 x)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		res[i] = mat_mult_vect_coef(a, x, i);
		i++;
	}
}

void	calc_rotation_figure(float3 ray, float3 v)
{
//	normalize(v);
	double	mat_x[3][3] = {
		{1, 0, 0},
		{0, v.z, -v.y},
		{0, v.y, v.z},
	};
	double	mat_y[3][3] = {
		{v.z, 0, -v.x},
		{0, 1, 0},
		{v.x, 0, v.z},
	};
	double	mat_z[3][3] = {
		{v.z, -v.x, 0},
		{v.x, v.z, 0},
		{0, 0, 1},
	};
	double	res[3][3];
	mat_mult(res, mat_y, mat_x);
	mat_mult_vect(ray, res, ray);
	(void)mat_y;
	(void)mat_z;
}
