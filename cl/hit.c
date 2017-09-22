float	calc_dist(float t, float3 ray)
{
	float3	cam_to_obj;
	float	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	cpy_vect(output->norm, output->intersect); // cpy dans obj norm
	output->intersect = add_vect(output->intersect, obj.pos);
}

void	assign_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	(void)pos;
	(void)ray;
	(void)t;
	if (obj.type == PLAN)
		output->norm = obj.dir;
}

int		hit(__global t_obj *objs, t_scene scene, float3 ray, struct s_result_hit *result_hit)
{
	float	dist;
	float3	pos_translated;
	float	t;
	int	i = 0;
	t_obj	obj;

	result_hit->obj = NULL;
	result_hit->dist = 100000.0;
//	printf ("scene objsnumber", scene.objs_number);
	while (i < scene.objs_number)
	{
			obj = objs[i];
			pos_translated = sub_vect(scene.cam_pos, obj.pos);
			t = calc_obj(&obj, pos_translated, ray); //TODO objs est ds la stack de la fct
			dist = calc_dist(t, ray);
			if (dist != 0 && dist < result_hit->dist)
			{
				result_hit->dist = dist;
				result_hit->t = t;
				result_hit->obj = &obj;
				assign_intersect_norm_vect(obj, t, pos_translated, ray, result_hit);
				assign_norm_vect(obj, t, pos_translated, ray, result_hit);
			}
		i++;
	}
	if (result_hit->obj == NULL)
		return (0);
	return (1);
}
