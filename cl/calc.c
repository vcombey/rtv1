size_t	calc_rayon(t_scene scene, float3 ray)
{
	t_obj	*shortest_obj;
	struct result_hit *output;

	shortest_obj = hit(scene, ray, output);
	if (shortest_obj)
		return (calc_all_lum(scene, shortest_obj, ray));
	return (0);
}

void	init_norm_cam_dir(float3 *norm_vert, float3 *norm_hor, float3 dir)
{
	normalize(dir);
	printf("dir %f, %f, %f\n", dir.x, dir.y,dir.z); 
	if (dir.y != 0)
	{
		norm_hor.z = 0;
		norm_hor.x = sqrt(dir.y * dir.y / (dir.x * dir.x + dir.y * dir.y));
		norm_hor.y = -dir.x / dir.y * norm_hor.x;
		if (norm_hor.y < 0)
			norm_hor.y *= -1;
	}
	else if (dir.x != 0)
	{
		norm_hor.z = 0;
		norm_hor.y = sqrt(dir.x * dir.x / (dir.x * dir.x + dir.y * dir.y));
		if (norm_hor.y < 0)
			norm_hor.y *= -1;
		norm_hor.x = -dir.y / dir.x * norm_hor.y;
	}
	normalize(norm_hor);
	vectorial_product(norm_vert, norm_hor, dir);
	normalize(norm_vert);
	printf("hor %f, %f, %f\n", norm_hor.x, norm_hor.y,norm_hor.z); 
	printf("vert %f, %f, %f\n", norm_vert.x, norm_vert.y,norm_vert.z); 
}

void	calc(
		t_scene scene
		__global t_obj *objs
		__global t_light *lights
		__global int *output,
		size_t height
		size_t width
		size_t width_per_height)
{
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];

	normalize(scene.cam.dir);
	init_norm_cam_dir(norm_vert, norm_hor, scene.cam.dir);

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

	size_t	pix_vert;
	size_t	pix_hor;
	int		i =  get_global_id(0);
	pix_hor = i % width;
	pix_vert = i / width;

	ray.x = scene.cam.dir.x;
	ray.y = scene.cam.dir.y;
	ray.z = scene.cam.dir.z;

	coef = (((double)pix_vert - ((double)height / 2)) / ((double)height / 2)) * 0.3; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.z += -coef * norm_vert.z;
	coef = (((double)pix_hor - ((double)width / 2)) / ((double)width / 2)) * 0.3 * width_per_height; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.y += coef * norm_hor.y;
	//printf("\nray %f, %f, %f\n", ray.x, ray.y, ray.z);
	output[i] = calc_rayon(scene, ray);
}
