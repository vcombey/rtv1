#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <OpenCL/opencl.h>

#include <mlx.h>
#include "mlx.h"
#include "rt.h"
#include "libft.h"
#include <stdio.h>
#include "cl.h"


int		calc_scene(struct s_cl *cl, struct s_cl_args *cl_args, t_env *env)
{
	cl_program program;                 // compute program
	char	*source_str;

	cl->data_size = env->width * env->height * sizeof(int);
	if (cl_init(cl))
		exit(1);
	if (file_to_str("./built.cl", &source_str))
		exit(1);
	if (cl_load_program_from_source(cl, &source_str, &program))
		exit(1);
	if (cl_create_kernel_from_program(program, "calc", &cl->kernel))
		exit(1);
	if (cl_create_buffer(cl, CL_MEM_WRITE_ONLY, cl->data_size, &cl->output))
		exit(1);
	if (cl_create_buffer(cl, CL_MEM_READ_ONLY, cl_args->objs_size, &cl_args->objs_buffer))
		exit(1);
	if (cl_create_buffer(cl, CL_MEM_READ_ONLY, cl_args->lights_size, &cl_args->lights_buffer))
		exit(1);
	if (cl_write_buffer(cl, cl_args->lights_buffer, cl_args->lights, cl_args->lights_size))
		exit(1);
	if (cl_write_buffer(cl, cl_args->objs_buffer, cl_args->objs, cl_args->objs_size))
		exit(1);
	int		i = 0;
	cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl->output);

		cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl_args->objs_buffer);
		cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl_args->lights_buffer);

		cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->height);
		cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->width);
		cl_set_arg(cl->kernel, sizeof(float), &i, &env->width_per_height);
		cl_set_arg(cl->kernel, sizeof(int), &i, &env->scene->objs_number);
		cl_set_arg(cl->kernel, sizeof(int), &i, &env->scene->lights_number);
		cl_set_arg(cl->kernel, sizeof(t_cam), &i, &env->scene->cam);

	if (cl_exec(cl, cl->data_size/ 4, cl->kernel))
		exit(1);
	if (cl_read_results(cl, cl->output, cl->data_size, (int *)env->ptr))
		exit(1);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (EXIT_SUCCESS);
}

int		recalc_scene(t_env *env)
{
	struct	s_cl *cl;
	struct s_cl_args *cl_args;

	cl = env->cl;
	cl_args = env->cl_args;
	recalc_img(env->scene);
	int		i = 0;
	cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl->output);

		cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl_args->objs_buffer);
		cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl_args->lights_buffer);
		cl_set_arg(cl->kernel, sizeof(t_scene2), &i, &env->scene2);
		cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->height);
		cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->width);
		cl_set_arg(cl->kernel, sizeof(float), &i, &env->width_per_height);

	if (cl_exec(cl, cl->data_size / 4, cl->kernel))
		exit(1);
	ft_memset(env->ptr, 0x00, env->width * env->height * 4);
	if (cl_read_results(cl, cl->output, cl->data_size, (int *)env->ptr))
		exit(1);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_env		*env;
	t_scene		scene;
	t_scene2	scene2;
	struct s_cl cl;
	struct s_cl_args cl_args;


	printf("coucou\n");
	if (ac != 2)
		fatal ("usage: rt_v1 <filename>");
	(void)ac;
	(void)av;
	init_scene(&scene);
	env = singleton_env();
	parse_file(av[1], &scene);
	env->width = scene.width;
	env->height = scene.height;
	env->name = "rt";
	//	printf("env width %zu, env height %zu env name %s\n", env->width, env->height, env->name);
	env->width_per_height = (float)env->width / (float)env->height;
	init_env(env);
	//	init_cam(&scene);


	ft_bzero(&cl, sizeof(struct s_cl));

	scene2.objs_number = scene.objs_number;
	scene2.lights_number = scene.lights_number;
	scene2.cam = scene.cam;
	env->cl = &cl;
	env->scene = &scene;
	env->scene2 = scene2;
	env->cl_args = &cl_args;


	cl_args.objs = scene.objs;
	cl_args.lights = scene.lights;
	cl_args.objs_size = scene.objs_number * sizeof(t_obj);
	cl_args.lights_size = scene.lights_number * sizeof(t_light);

	env->cl_args = &cl_args;

	calc_scene(&cl, &cl_args, env);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, &ft_key_pressed, env);
	mlx_hook(env->win, KEYRELEA, KEYRELEAMASK, &ft_key_release, env);
	mlx_loop_hook(env->mlx, recalc_scene, env);
	mlx_hook(env->win, 17, 1, &quit, NULL);
	mlx_loop(env->mlx);
	/*	clReleaseMemObject(output);
		clReleaseProgram(program);
		clReleaseKernel(kernel);
		clReleaseCommandQueue(commands);
		clReleaseContext(context);
		*/
	return 0;
}
