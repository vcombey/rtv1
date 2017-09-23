int	obj_between_light(t_scene scene, __global t_obj *objs, t_light lum, float3 lum_vect, struct s_result_hit  hit_forward)
{
	struct s_result_hit hit_backward;
	float3		obj_obj;
	float3		obj_light;

	lum_vect = mult_vect(lum_vect, -1);
	if (!hit(objs, scene.objs_number, hit_forward.intersect, lum_vect, &hit_backward))
		return (0);
	obj_obj = sub_vect(hit_forward.intersect, hit_backward.intersect);
	obj_light = sub_vect(hit_forward.intersect, lum.pos);
//	if (hit_forward.obj == hit_backward.obj)
//		return (0);
	if (norme_carre(obj_obj) < norme_carre(obj_light))
	{
//		printf("ombre\n");
		return (1);
	}
//	printf("\nobj_intersect x %f\ny %f\nz %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
//	printf("\nhit_obj_intersect x %f\ny %f\nz %f\n", hit_obj_intersect.x, hit_obj_intersect.y, hit_obj_intersect.z);
	return (0);
}
