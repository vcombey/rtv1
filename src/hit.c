#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

void	translate_base(double res[3], double scene_cam_pos[3], double obj_pos[3])
{
	ft_memset(res, 0, sizeof(double) * 3);
	sub_vect(res, scene_cam_pos, obj_pos);
}

size_t	calc_dist(double t, double ray[3])
{
	double	cam_to_obj[3];
	size_t	dist;

	mult_vect(cam_to_obj, ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj *obj, double t, double pos[3], double ray[3])
{
	mult_vect(obj->intersect, ray, t);
	add_vect(obj->intersect, obj->intersect, pos);
	add_vect(obj->intersect, obj->intersect, obj->pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
}

t_obj	*hit(t_scene *scene, double *scene_cam_pos, double ray[3])
{
	t_obj	*tmp;
	t_obj	*shortest_obj;
	size_t	min_dist;
	size_t	dist;
	double	pos[3];
	double	t;

	shortest_obj = NULL;
	min_dist = (size_t)-1;
	tmp = scene->objs;
	while (tmp)
	{
		translate_base(pos, scene_cam_pos, tmp->pos);
		t = tmp->f(tmp, pos, ray);
		dist = calc_dist(t, ray);
		assign_intersect_norm_vect(tmp, t, pos, ray);
		if (dist != 0 && dist < min_dist)
		{
			shortest_obj = tmp;
			min_dist = dist;
		}
		tmp = tmp->next;
	}
	return (shortest_obj);
}
