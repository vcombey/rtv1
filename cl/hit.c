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

void	assign_intersect_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
}

void	assign_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	float	teta;
	(void)pos;
	(void)ray;
	(void)t;
	output->norm = output->intersect; //c'est le vecteur d intersection si la position de lobjet vaut 0
	if (obj.type == PLAN)
		output->norm = obj.dirz;
	if (obj.type == CYLINDRE)
		output->norm.z = 0;
	if (obj.type == CONE)
	{
		float3	hor;
		hor = output->norm;
		hor.z = 0;
		if (output->intersect.z > 0)
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
	float3	pos_transformed;
	float3	ray_transformed;
	float	t;
	int	i = 0;
	t_obj	obj;
	int		hit;
	float matrix[3][3];
	float inverted_matrix[3][3];

	hit = 0;
	result_hit->dist = 100000.0;
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
			dist = calc_dist(t, ray_transformed, &obj);
			if (dist > 0.0001 && dist < result_hit->dist)
			{
				hit = 1;
				result_hit->dist = dist;
				result_hit->t = t;
				result_hit->obj = obj;
				assign_intersect_vect(obj, t, pos_transformed, ray_transformed, result_hit);
				assign_norm_vect(obj, t, pos_transformed, ray_transformed, result_hit); //must be call just after asign_intersect_vect
				if (obj.type != PLAN && obj.type != SPHERE)
				{
					result_hit->intersect = mat_mult_vect(matrix, result_hit->intersect);
					result_hit->intersect = add_vect(result_hit->intersect, obj.pos);
					result_hit->norm = mat_mult_vect(matrix, result_hit->norm);
					result_hit->ray = mat_mult_vect(matrix, ray_transformed);
				}
				else
				{
					result_hit->intersect = add_vect(result_hit->intersect, obj.pos);
					result_hit->ray = ray;
				}
			}
		i++;
	}
	if (!hit)
		return (0);
	return (1);
}
