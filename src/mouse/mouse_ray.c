/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 16:46:56 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>

float	calc_dist(float t, cl_float3 ray)
{
	cl_float3	cam_to_obj;
	float	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	return (dist);
}
int		hit(t_obj *objs, int objs_number, cl_float3 cam_pos, cl_float3 ray,  struct s_result_hit *result_hit)
{
	float		dist;
	cl_float3	pos_transformed;
	cl_float3	ray_transformed;
	float		t;
	int			i;
	t_obj		obj;
	int			hit;
	float matrix[3][3];
	float inverted_matrix[3][3];

	i = 0;
	hit = 0;
	result_hit->dist = 1000.0;
	while (i < objs_number)
	{
		obj = objs[i];
		pos_transformed = sub_vect(cam_pos, obj.pos);
		if (obj.type != PLAN && obj.type != SPHERE)
		{
			set_rotation_matrix(matrix, obj.dirx, obj.diry, obj.dirz);
			invert_matrix(matrix, inverted_matrix);
			pos_transformed = mat_mult_vect(inverted_matrix, pos_transformed);
			ray_transformed = mat_mult_vect(inverted_matrix, ray);
		}
		else
			ray_transformed = ray;
		t = calc_obj(&obj, pos_transformed, ray_transformed);
		if (t < 0.001)
			t = 0;
		dist = calc_dist(t, ray);
		if (dist > 0.0001 && dist < result_hit->dist)
		{
			hit = 1;
			result_hit->dist = dist;
			result_hit->indice = i;
			result_hit->t = t;
			result_hit->obj = obj;
		}
		i++;
	}
	if (!hit)
		return (0);
	return (1);
}

int		mouse_event(int button, int x, int y)
{
	if (button == 1)
	{
		cl_float3			ray;
		float				coef;
		t_env				*env;
		struct s_result_hit	result_hit;
		cl_float3			cam_dir;

		env = singleton_env();
		cam_dir = env->scene->cam.dir;
		ray.x = cam_dir.x;
		ray.y = cam_dir.y;
		ray.z = cam_dir.z;
		ray = NORMALIZE(ray);
		coef = (((float)y - ((float)env->height / 2)) / ((float)env->height / 2)) * 0.3;
		ray.z += -coef * env->scene->norm_vert.z;
		coef = (((float)x - ((float)env->width / 2)) / ((float)env->width / 2)) * 0.3 * env->width_per_height;
		ray.y += coef * env->scene->norm_hor.y;
		ray.x += coef * env->scene->norm_hor.x;
		ray = NORMALIZE(ray);
		if (hit(env->scene->objs, env->scene->objs_number, env->scene->cam.pos, ray, &result_hit))
			env->indice_obj = result_hit.indice;
	}
	return (1);
}
