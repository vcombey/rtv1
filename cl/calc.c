int	calc_rayon(t_scene scene, float3 ray)
{
	struct s_result_hit *result_hit;

	if (hit(scene, ray, result_hit))
		return (calc_all_lum(scene, result_hit, ray));
	return (0);
}

__kernel void	calc(__global int *output, __global t_obj *objs, __global t_light *lights, t_scene scene, int height, int width, float width_per_height)
{
	float3	ray;
	float	coef;
	float3	norm_vert;
	float3	norm_hor;

	/*
**	 	norm_vert.x = 0;
**	 	norm_vert.y = 0;
**	 	norm_vert.z = 1;
**	
**	 	norm_hor.x = -1;
**	 	norm_hor.y = 0;
**	 	norm_hor.z = 0;
**	
*/

	int	pix_vert;
	int	pix_hor;
	int		i =  get_global_id(0);
	pix_hor = i % width;
	pix_vert = i / width;

	ray.x = scene.cam.dir.x;
	ray.y = scene.cam.dir.y;
	ray.z = scene.cam.dir.z;

	coef = (((float)pix_vert - ((float)height / 2)) / ((float)height / 2)) * 0.3; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.z += -coef * norm_vert.z;
	coef = (((float)pix_hor - ((float)width / 2)) / ((float)width / 2)) * 0.3 * width_per_height; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.y += coef * norm_hor.y;
	//printf("\nray %f, %f, %f\n", ray.x, ray.y, ray.z);
	output[i] = calc_rayon(scene, ray);
}
