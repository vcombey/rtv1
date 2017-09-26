#include "rt.h"
#include <math.h>

void	init_norm_cam_dir(cl_float3 *norm_vert, cl_float3 *norm_hor, cl_float3 dir)
{
	dir = normalize(dir);
//	printf("dir %f, %f, %f\n", dir.x, dir.y,dir.z); 
	*norm_hor = rot(dir, M_PI / 2);
	norm_hor->z = 0;
	*norm_vert = vectorial_product(dir, *norm_hor);
	*norm_hor = normalize(*norm_hor);
	*norm_vert = normalize(*norm_vert);
	/*
**		if (dir.y != 0)
**		{
**			norm_hor->z = 0;
**			norm_hor->x = sqrt(dir.y * dir.y / (dir.x * dir.x + dir.y * dir.y));
**			norm_hor->y = -dir.x / dir.y * norm_hor->x;
**			if (norm_hor->y < 0)
**				norm_hor->y *= -1;
**		}
**		else if (dir.x != 0)
**		{
**			norm_hor->z = 0;
**			norm_hor->y = sqrt(dir.x * dir.x / (dir.x * dir.x + dir.y * dir.y));
**			if (norm_hor->y < 0)
**				norm_hor->y *= -1;
**			norm_hor->x = -dir.y / dir.x * norm_hor->y;
**		}
**		*norm_hor = normalize(*norm_hor);
**		*norm_vert = vectorial_product(*norm_hor, dir);
**		*norm_vert = normalize(*norm_vert);
*/
//	printf("hor %f, %f, %f\n", norm_hor->x, norm_hor->y,norm_hor->z); 
//	printf("vert %f, %f, %f\n", norm_vert->x, norm_vert->y,norm_vert->z); 
}
