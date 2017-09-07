#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

int		hit_ombre(double intersect[3], t_scene *scene, double *scene_cam_pos, double ray[3])
{
	t_obj	*tmp;
	t_obj	*shortest_obj;
	size_t	min_dist;
	size_t	dist;
	double	pos[3];
	double	t;
	double	min_t;

	shortest_obj = NULL;
	min_dist = (size_t)-1;
	tmp = scene->objs;
	while (tmp)
	{
		translate_base(pos, scene_cam_pos, tmp->pos);
		t = tmp->f(tmp, pos, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < min_dist)
		{
			min_t = t;
			shortest_obj = tmp;
			min_dist = dist;
		}
		tmp = tmp->next;
	}
	if (!shortest_obj)
		return (0);
	mult_vect(intersect, ray, t);
	add_vect(intersect, intersect, pos);
	add_vect(intersect, intersect, shortest_obj->pos);
	cpy_vect(shortest_obj->norm, intersect); // cpy dans obj norm
	return (1);
}

size_t	obj_between_light(t_scene *scene, t_obj *obj, t_light *lum, double *lum_vect)
{
	double	hit_obj_intersect[3];
	double	obj_obj[3];
	double	obj_light[3];
	double	lum_vect_cpy[3];

	mult_vect(lum_vect_cpy, lum_vect, -1);
	if (!hit_ombre(hit_obj_intersect, scene, obj->intersect, lum_vect_cpy))
		return (0);
	sub_vect(obj_obj, obj->intersect, hit_obj_intersect);
	sub_vect(obj_light, obj->intersect, lum->pos);
	if (norme_carre(obj_obj) < norme_carre(obj_light))
		return (1);
	return (0);
}
