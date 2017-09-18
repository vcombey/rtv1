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


int		calc_scene(struct s_cl *cl, t_env *env)
{
	cl_program program;                 // compute program
	char	*source_str;

	cl->data_size = env->width * env->height * sizeof(int);
	if (cl_init(cl))
		exit(1);
	if (file_to_str("./cl/calc2.cl", &source_str))
		exit(1);
	if (cl_load_program_from_source(cl, &source_str, &program))
		exit(1);
	if (cl_create_kernel_from_program(program, "calc", &cl->kernel))
		exit(1);
	if (cl_create_buffer(cl, CL_MEM_WRITE_ONLY, cl->data_size, &cl->output))
		exit(1);
	int		i = 0;
	cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl->output);
	cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->height);
	cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->width);
	cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->startx);
	cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->starty);
	size_t size = 250;
	cl_set_arg(cl->kernel, sizeof(size_t), &i, &size);
	if (cl_exec(cl, cl->data_size / 4, cl->kernel))
		exit(1);
	if (cl_read_results(cl, cl->output, cl->data_size, (int *)env->ptr))
		exit(1);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (EXIT_SUCCESS);
}

int		recalc_scene(t_env *env)
{
	struct	s_cl *cl;
	t_scene		s;
	cl = env->cl;
	mv_up(env, &s.cam);
	mv_down(env, &s.cam);
	rot_right(env, &s.cam);
	rot_left(env, &s.cam);


int		i = 0;
cl_set_arg(cl->kernel, sizeof(cl_mem), &i, &cl->output);
cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->height);
cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->width);
cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->startx);
cl_set_arg(cl->kernel, sizeof(size_t), &i, &env->starty);
size_t size = 250;
cl_set_arg(cl->kernel, sizeof(size_t), &i, &size);
if (cl_exec(cl, cl->data_size / 4, cl->kernel))
	exit(1);
if (cl_read_results(cl, cl->output, cl->data_size, (int *)env->ptr))
	exit(1);
mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
return (EXIT_SUCCESS);
}


int		main(int ac, char **av)
{
	t_env	*env;
	t_scene	scene;


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
	env->startx = 250;
	env->starty = 250;
	//	printf("env width %zu, env height %zu env name %s\n", env->width, env->height, env->name);
	env->width_per_height = (double)env->width / (double)env->height;
	init_env(env);
	//	init_cam(&scene);

	struct s_cl cl;

	ft_bzero(&cl, sizeof(struct s_cl));

	calc_scene(&cl, env);
	env->cl = &cl;

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
