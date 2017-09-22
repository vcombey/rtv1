int	calc_rayon(__global t_obj *objs, __global t_light *lights, t_scene scene, float3 ray)
{
	struct s_result_hit *result_hit;

	if (hit(objs, scene, ray, result_hit))
		return (calc_all_lum(lights, scene, result_hit, ray));
	return (0);
}

void	debug_light(t_scene scene, __global t_light *lights)
{
	int		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene.lights_number)
	{
		printf("pos %f, %f, %f\n", lights[i].pos.x, lights[i].pos.y, lights[i].pos.z);
		i++;
	}
}

void	debug_obj(t_scene scene,  __global t_obj *objs)
{
	int		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene.objs_number)
	{
		printf("\nname %d\n", objs[i].type);
		printf("color %zX\n", objs[i].color);
		//printf("dir %f, %f, %f\n", objs[i].dir.x, objs[i].dir.y, objs[i].dir.z);
		printf("pos %f, %f, %f\n", objs[i].pos.x, objs[i].pos.y, objs[i].pos.z);
		printf("alpha %f\n", objs[i].alpha);
		printf("rayon %f\n\n", objs[i].rayon);
		i++;
	}
}

void	debug_scene(t_scene scene, __global t_obj *objs, __global t_light *lights)
{

	printf("scenenb %f\n", scene.objs_number);
	printf("scenenb %f\n", scene.lights_number);
	
//	printf("campos %f, %f, %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
//	printf("camdir %f, %f, %f\n", scene->cam.dir.x, scene->cam.dir.y, scene->cam.dir.z);
	debug_obj(scene, objs);
	debug_light(scene, lights);
}

__kernel void	calc(__global int *output, __global t_obj *objs, __global t_light *lights, int height, int width, float width_per_height, int objs_number, int lights_number, t_cam cam)
{
	float3	ray;
	float	coef;
	float3	norm_vert;
	float3	norm_hor;
	t_scene	scene;

	scene.objs_number = objs_number;
	scene.lights_number = lights_number;
//	scene.cam = cam;
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
	printf("coucou");
	if (i == 1)
	{
		printf("lala");
		debug_scene(scene, objs, lights);
	}
	printf("coucou");
	pix_hor = i % width;
	pix_vert = i / width;

	ray.x = scene.cam.dir.x;
	ray.y = scene.cam.dir.y;
	ray.z = scene.cam.dir.z;

	coef = (((float)pix_vert - ((float)height / 2)) / ((float)height / 2)) * 0.3; //varie entre -0.66 et +0.66
//	printf("coef %f\n", coef);
	ray.z += -coef * norm_vert.z;
	coef = (((float)pix_hor - ((float)width / 2)) / ((float)width / 2)) * 0.3 * width_per_height; //varie entre -0.66 et +0.66
//	printf("coef %f\n", coef);
	ray.y += coef * norm_hor.y;
//	printf("\nray %f, %f, %f\n", ray.x, ray.y, ray.z);
	output[i] = calc_rayon(objs, lights, scene, ray);
}
