#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_dist(double t, float3 ray)
{
	float3	cam_to_obj;
	size_t	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj *obj, double t, float3 pos, float3 ray, struct result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	output->intersect = add_vect(output->intersect, obj->pos);
}

void	assign_norm_vect(t_obj *obj, double t, float3 pos, float3 ray)
{
	(void)pos;
	(void)ray;
	(void)t;
	if (obj->type == PLAN)
		cpy_vect(obj->norm, obj->dir); // cpy dans obj norm
}

int		hit(t_scene *scene, float3 scene_cam_pos, float3 ray, t_obj *shortest_obj, struct result_hit *output)
{
	size_t	min_dist;
	size_t	dist;
	float3	pos_tranlated;
	double	t;
	size_t	i = 0;
	t_obj	*obj;

	output->obj = NULL;
	output->dist = (size_t)-1;
	while (i < scene.objs_number)
	{
		obj = scene.objs + i;
		pos_translated = sub_vect(scene_cam_pos, obj_pos);
		t = (obj, pos_translated, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < output->dist)
		{
			output->dist = dist;
			output->t = t;
			output->obj = obj;
			assign_intersect_norm_vect(tmp, t, translated_pos, ray, output);
			assign_norm_vect(tmp, t, pos, ray, output);
		}
		i++;
	}
	if (output->obj == NULL)
		return (0);
	return (1);
}
