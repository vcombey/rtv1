#include "rt.h"
#include <math.h>
float	norme_carre(cl_float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	scalar_product(cl_float3 u, cl_float3 v)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

cl_float3	NORMALIZE(cl_float3 v)
{
	return (div_vect(v, sqrt(norme_carre(v))));
}
