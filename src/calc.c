#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

void	translate_base(t_obj *obj, double cam_pos[3], double scene_cam_pos[3])
{
	ft_memset(cam_pos, 0, sizeof(double) * 3);
	sub_vect(cam_pos, scene_cam_pos, obj->pos);
}

t_obj	*hit(t_scene *scene, double *scene_cam_pos, double ray[3])
{
	t_obj	*tmp;
	t_obj	*shortest_obj;
	size_t	min_dist;
	size_t	dist;
	t_cam	cam;

	shortest_obj = NULL;
	min_dist = (size_t)-1;
	tmp = scene->objs;
	while (tmp)
	{
		translate_base(tmp, cam.pos, scene_cam_pos);
		dist = tmp->f(tmp, cam, ray);
		if (dist != 0 && dist < min_dist)
		{
			shortest_obj = tmp;
			min_dist = dist;
		}
		tmp = tmp->next;
	}
	return (shortest_obj);
}

size_t	calc_rayon(t_scene *scene, double ray[3])
{
	t_obj	*shortest_obj;

	shortest_obj = hit(scene, scene->cam.pos, ray);
	if (shortest_obj)
		return (calc_all_lum(scene, shortest_obj, ray));
	return (0);
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

	ray[0] = -1;
	ray[1] = 0;
	ray[2] = 0;

	norm_vert[0] = 0;
	norm_vert[1] = 0;
	norm_vert[2] = -1;

	norm_hor[0] = 0;
	norm_hor[1] = 1;
	norm_hor[2] = 0;

	pix_vert = 0;
	pix_hor = 0;

	while (pix_vert < SCREEN_HEIGHT)
	{

		pix_hor = 0;
		while (pix_hor < SCREEN_WIDTH)
		{
			ray[0] = -1;
			ray[1] = 0;
			ray[2] = 0;

			coef = (((double)pix_vert - ((double)env->height / 2)) / ((double)env->height / 2)) * 0.3; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[2] += coef * norm_vert[2];
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
