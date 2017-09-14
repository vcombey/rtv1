#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_rayon(t_scene *scene, double ray[3])
{
	t_obj	*shortest_obj;

	shortest_obj = hit(scene, scene->cam.pos, ray);
	if (shortest_obj)
		return (calc_all_lum(scene, shortest_obj, ray));
	return (0);
}

void	init_norm_cam_dir(double norm_vert[3], double norm_hor[3], double dir[3])
{
	if (dir[1] != 0)
	{
		norm_hor[2] = 0;
		norm_hor[0] = sqrt(dir[1] * dir[1] / (dir[0] * dir[0] + dir[1] * dir[1]));
		norm_hor[1] = -dir[0] / dir[1] * norm_hor[0];
		if (norm_hor[1] < 0)
			norm_hor[1] *= -1;
	}
	else if (dir[0] != 0)
	{
		norm_hor[2] = 0;
		norm_hor[1] = sqrt(dir[0] * dir[0] / (dir[0] * dir[0] + dir[1] * dir[1]));
		if (norm_hor[1] < 0)
			norm_hor[1] *= -1;
		norm_hor[0] = -dir[1] / dir[0] * norm_hor[1];
	}
	normalize(norm_hor);
	normalize(dir);
	vectorial_product(norm_vert, norm_hor, dir);
	normalize(norm_vert);
}

void	calc(t_env *env, t_scene *scene)
{
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];
	size_t	pix_vert;
	size_t	pix_hor;

	assign_obj_func(scene);
	(void)scene;
	normalize(scene->cam.dir);

	init_norm_cam_dir(norm_vert, norm_hor, scene->cam.dir);

	/*
**	 	norm_vert[0] = 0;
**	 	norm_vert[1] = 0;
**	 	norm_vert[2] = 1;
**	
**	 	norm_hor[0] = -1;
**	 	norm_hor[1] = 0;
**	 	norm_hor[2] = 0;
**	
*/


	pix_vert = 0;
	pix_hor = 0;

	while (pix_vert < SCREEN_HEIGHT)
	{

		pix_hor = 0;
		while (pix_hor < SCREEN_WIDTH)
		{
			ray[0] = scene->cam.dir[0];
			ray[1] = scene->cam.dir[1];
			ray[2] = scene->cam.dir[2];

			coef = (((double)pix_vert - ((double)env->height / 2)) / ((double)env->height / 2)) * 0.3; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[2] += -coef * norm_vert[2];
			coef = (((double)pix_hor - ((double)env->width / 2)) / ((double)env->width / 2)) * 0.3 * env->width_per_height; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[1] += coef * norm_hor[1];
			//printf("\nray %f, %f, %f\n", ray[0], ray[1], ray[2]);
			ft_pixelput(env, pix_hor, pix_vert, calc_rayon(scene, ray));
			pix_hor++;
		}
		pix_vert++;
	}
}
