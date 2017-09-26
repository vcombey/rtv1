#include "rt.h"
#include <math.h>

void	init_norm_cam_dir(cl_float3 *norm_vert, cl_float3 *norm_hor, cl_float3 dir)
{
	dir = normalize(dir);
	*norm_hor = rot(dir, M_PI / 2);
	norm_hor->z = 0;
	*norm_vert = vectorial_product(dir, *norm_hor);
	*norm_hor = normalize(*norm_hor);
	*norm_vert = normalize(*norm_vert);
}
