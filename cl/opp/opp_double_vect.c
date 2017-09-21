#include <math.h>
#include "rt.h"

double	norme_carre(float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	scalar_product(float3 u, float3 v)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

float3	normalize(float3 v)
{
	return (div_vect(v, v, sqrt(norme_carre(v))));
}
