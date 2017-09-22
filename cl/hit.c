int	calc_dist(float t, float3 ray)
{
	float3	cam_to_obj;
	int	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj *obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	cpy_vect(output->norm, output->intersect); // cpy dans obj norm
	output->intersect = add_vect(output->intersect, obj->pos);
}

void	assign_norm_vect(t_obj *obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	(void)pos;
	(void)ray;
	(void)t;
	if (obj->type == PLAN)
		output->norm = obj->dir;
}

int		hit(t_scene scene, float3 ray, struct s_result_hit *output)
{
	int	dist;
	float3	pos_translated;
	float	t;
	int	i = 0;
	t_obj	*obj;

	output->obj = NULL;
	output->dist = (int)-1;
	while (i < scene.objs_number)
	{
		obj = scene.objs + i;
		pos_translated = sub_vect(scene.cam.pos, obj->pos);
		t = calc_obj(obj, pos_translated, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < output->dist)
		{
			output->dist = dist;
			output->t = t;
			output->obj = obj;
			assign_intersect_norm_vect(obj, t, pos_translated, ray, output);
			assign_norm_vect(obj, t, pos_translated, ray, output);
		}
		i++;
	}
	if (output->obj == NULL)
		return (0);
	return (1);
}
