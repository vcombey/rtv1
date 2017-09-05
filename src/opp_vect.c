#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

void	mult_vect(double res[3], double v[3], double t)
{
	res[0] = v[0] * t;
	res[1] = v[1] * t;
	res[2] = v[2] * t;
}

void	div_vect(double res[3], double v[3], double t)
{
	if (t == 0)
		return ;
	res[0] = v[0] / t;
	res[1] = v[1] / t;
	res[2] = v[2] / t;
}

void	add_vect(double res[3], double u[3], double v[3])
{
	res[0] = u[0] + v[0];
	res[1] = u[1] + v[1];
	res[2] = u[2] + v[2];
}

void	cpy_vect(double u[3], double v[3])
{
	u[0] = v[0];
	u[1] = v[1];
	u[2] = v[2];
}

void	sub_vect(double res[3], double u[3], double v[3])
{
	res[0] = u[0] - v[0];
	res[1] = u[1] - v[1];
	res[2] = u[2] - v[2];
}
