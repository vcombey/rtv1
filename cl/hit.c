float	calc_dist(float t, float3 ray, t_obj *obj)
{
	float3	cam_to_obj;
	float	dist;

	(void)obj;
	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	
	/*
**			if (dist < 0.1)
**				return (0);
*/

	return (dist);
}

void	assign_intersect_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	output->norm = output->intersect; //c'est le vecteur d intersection si la position de lobjet vaut 0
	output->intersect = add_vect(output->intersect, obj.pos);
}

void	assign_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	float	teta;
	(void)pos;
	(void)ray;
	(void)t;
	if (obj.type == PLAN)
		output->norm = obj.dir;
	if (obj.type == CYLINDRE)
		output->norm.z = 0;
	if (obj.type == CONE)
	{
		float3	hor;
		hor = output->norm;
		hor.z = 0;
		if (output->intersect.z > obj.pos.z)
			teta = M_PI / 2;
		else
			teta = -M_PI / 2;
		hor = rot(hor, -M_PI/2);
		output->norm = rodrigues(output->norm, hor, -teta);
		//output->norm.z = 0;
	}
}

int		hit(__global t_obj *objs, int objs_number, float3 cam_pos, float3 ray,  struct s_result_hit *result_hit)
{
	float	dist;
	float3	pos_translated;
	float	t;
	int	i = 0;
	t_obj	obj;
	int		hit;

	hit = 0;
	result_hit->dist = 100000.0;
//	printf ("scene objsnumber", scene.objs_number);
	while (i < objs_number)
	{
			obj = objs[i];
			pos_translated = sub_vect(cam_pos, obj.pos);
		//	printf("scene.cam_pos %f, %f, %f", scene.cam_pos.x, scene.cam_pos.y, scene.cam_pos.z);
			t = calc_obj(&obj, pos_translated, ray); //TODO objs est ds la stack de la fct
			if (obj.type != PLAN && obj.type != SPHERE)
				result_hit->ray = calc_rotation_figure(ray, obj.dir);
			else
				result_hit->ray = ray;
			//printf("t %f", t );
			dist = calc_dist(t, result_hit->ray, &obj);
			if (dist > 0.0001 && dist < result_hit->dist)
			{
		//	printf("dist %f", dist);
				hit = 1;
				result_hit->dist = dist;
				result_hit->t = t;
				result_hit->obj = obj;
				assign_intersect_norm_vect(obj, t, pos_translated, result_hit->ray, result_hit);
				assign_norm_vect(obj, t, pos_translated, result_hit->ray, result_hit);
			}
		i++;
	}
	if (!hit)
		return (0);
	return (1);
}
