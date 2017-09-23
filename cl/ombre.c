int		hit_ombre(float3 intersect, t_scene *scene, float *scene_cam_pos, float3 ray, t_obj *obj)
{
	t_obj	*tmp;
	t_obj	*shortest_obj;
	int	min_dist;
	int	dist;
	float3 pos;
	float	t;
	float	min_t;

	shortest_obj = NULL;
	min_dist = (int)-1;
	tmp = scene->objs;
	while (tmp)
	{
		translate_base(pos, scene_cam_pos, tmp->pos);
		t = tmp->f(tmp, pos, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < min_dist && tmp != obj)
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
	return (1);
}

int	obj_between_light(t_scene *scene, t_obj *obj, t_light *lum, float lum_vect, struct hit_result hit_forward)
{
	struct hit_result hit_backward;
	float3		hit_obj_intersect;
	float3		obj_obj;
	float3		obj_light;

	lum_vect = mult_vect(lum_vect, -1);
	if (!hit_ombre(hit_obj_intersect, scene,, lum_vect, obj))
		return (0);
	obj_obj = sub_vect(hit_forward->intersect, hit_obj_intersect);
	obj_light = sub_vect(hit_forward->intersect, lum->pos);
	if (norme_carre(obj_obj) < norme_carre(obj_light))
	{
//		printf("ombre\n");
		return (1);
	}
//	printf("\nobj_intersect x %f\ny %f\nz %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
//	printf("\nhit_obj_intersect x %f\ny %f\nz %f\n", hit_obj_intersect.x, hit_obj_intersect.y, hit_obj_intersect.z);
	return (0);
}
