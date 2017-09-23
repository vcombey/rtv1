#include "rt.h"
#include <stdio.h>

float	calc_dist(float t, cl_float3 ray)
{
	cl_float3	cam_to_obj;
	float	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	/*
**		if (dist < 0.1)
**			return (0);
*/
	return (dist);
}

int		hit(t_obj *objs, int objs_number, cl_float3 cam_pos, cl_float3 ray,  struct s_result_hit *result_hit)
{
	float	dist;
	cl_float3	pos_translated;
	float	t;
	int	i = 0;
	t_obj	obj;
	int		hit;

	hit = 0;
	result_hit->dist = 1000.0;
//	printf ("scene objsnumber", scene.objs_number);
	while (i < objs_number)
	{
		obj = objs[i];
		pos_translated = sub_vect(cam_pos, obj.pos);
	//	printf("scene.cam_pos %f, %f, %f", scene.cam_pos.x, scene.cam_pos.y, scene.cam_pos.z);
		t = calc_obj(&obj, pos_translated, ray); //TODO objs est ds la stack de la fct
		//printf("t %f", t );
		dist = calc_dist(t, ray);
		if (dist > 0.0001 && dist < result_hit->dist)
		{
	//	printf("dist %f", dist);
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
	printf("button %d", button);
	printf("mouse x %d", x);
	printf("mouse y %d", y);
	if (button == 1)
	{
		cl_float3	ray;
		float	coef;
		t_env	*env;
		struct s_result_hit result_hit;
		cl_float3	cam_dir;

		env = singleton_env();
		cam_dir = env->scene->cam.dir;
		ray.x = cam_dir.x;
		ray.y = cam_dir.y;
		ray.z = cam_dir.z;

		ray = NORMALIZE(ray);
		coef = (((float)y - ((float)env->height / 2)) / ((float)env->height / 2)) * 0.3; //varie entre -0.66 et +0.66
		ray.z += -coef * env->scene->norm_vert.z;
		coef = (((float)x - ((float)env->width / 2)) / ((float)env->width / 2)) * 0.3 * env->width_per_height; //varie entre -0.66 et +0.66
		ray.y += coef * env->scene->norm_hor.y;
		ray.x += coef * env->scene->norm_hor.x;
		ray = NORMALIZE(ray);

		if (hit(env->scene->objs, env->scene->objs_number, env->scene->cam.pos, ray, &result_hit))
		{
			printf("name %d\n",result_hit.obj.type);
		}
	}
	return (1);
}
