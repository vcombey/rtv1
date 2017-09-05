#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

void	calc_pixel(t_env *env)
{
	(void)env;
}

size_t	calc_lum(t_obj *obj)
{
	double	lum_pos[3];
	double	lum_vect[3];
	double	lum;
	size_t	intensite_lum;

	lum_pos[0] = 3;
	lum_pos[1] = 1;
	lum_pos[2] = 1;

	sub_vect(lum_pos, lum_pos, obj->pos);
	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum_vect, obj->intersect, lum_pos);
	normalize(lum_vect);
	normalize(obj->norm);
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	lum = scalar_product(lum_vect, obj->norm);
/*
**		if (lum > 0)
**			return (0x001000);
*/
	lum = ft_abs_double(lum);
	//		printf("lum %f\n", lum);
	intensite_lum = (size_t)(lum * (obj->color >> 16)) << 16;
	intensite_lum += (size_t)(lum * ((obj->color & 0xFF00) >> 8)) << 8;
	intensite_lum += lum * (obj->color & 0xFF);
	return (intensite_lum);
//	return (((size_t)(lum * (obj->color >> 16)) << 16) & (((size_t)(lum * (obj->color & 0xFF00 >> 8)) << 8) & ((size_t)(lum * (obj->color & 0xFF))));
	//		printf("intensite_obj->color %zu\n", intensite_obj->color);
}

void	translate_base(t_obj *obj, double cam_pos[3], double scene_cam_pos[3])
{
	ft_memset(cam_pos, 0, sizeof(double) * 3);
	sub_vect(cam_pos, scene_cam_pos, obj->pos);
}

size_t	hit(t_scene *scene, double ray[3])
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
		translate_base(tmp, cam.pos, scene->cam.pos);
		dist = tmp->f(tmp, cam, ray);
		if (dist != 0 && dist < min_dist)
		{
			shortest_obj = tmp;
			min_dist = dist;
		}
		tmp = tmp->next;
	}
	if (shortest_obj)
		return (calc_lum(shortest_obj));
	else
		return (0);
}

void	calc(t_env *env, t_scene *scene)
{
	t_cam	cam;
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];
	size_t	pix_vert;
	size_t	pix_hor;

	assign_obj_func(scene);
	(void)scene;
	cam.pos[0] = 3;
	cam.pos[1] = 0;
	cam.pos[2] = 0;

	cam.dir[0] = -1;
	cam.dir[1] = 0;
	cam.dir[2] = 0;

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
		
			ray[0] = -0.66;
			ray[1] = 0;
			ray[2] = 0;

			coef = (((double)pix_vert - ((double)env->height / 2)) / ((double)env->height / 2)) * 0.66; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[2] += coef * norm_vert[2];
			coef = (((double)pix_hor - ((double)env->width / 2)) / ((double)env->width / 2)) * 0.66 * env->width_per_height; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[1] += coef * norm_hor[1];
			//printf("\nray %f, %f, %f\n", ray[0], ray[1], ray[2]);
			ft_pixelput(env, pix_hor, pix_vert, hit(scene, ray));
			/*
			double	hit_sphere = calc_sphere(cam, ray);
**				if (hit_sphere > 0)
**					ft_pixelput(env, pix_hor, pix_vert, hit_sphere);
**				else
**					ft_pixelput(env, pix_hor, pix_vert, calc_plan(cam, ray));
*/
			pix_hor++;
		}
		pix_vert++;
	}
}
