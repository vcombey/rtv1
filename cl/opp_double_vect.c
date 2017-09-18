#include <math.h>
#include "rt.h"

double	norme_carre(double v[3])
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

double	scalar_product(double u[3], double v[3])
{
	return (v[0] * u[0] + v[1] * u[1] + v[2] * u[2]);
}

void	normalize(double v[3])
{
	div_vect(v, v, sqrt(norme_carre(v)));
}
