#include <mlx.h>
#include "mlx.h"
#include "rt.h"
#include "libft.h"
#include <stdio.h>

t_env	*singleton_env()
{
	static t_env	env;

	return (&env);
}

void	init_scene(t_scene *scene)
{
	scene->objs = NULL;
	scene->lights = NULL;
}


int	quit(void *param)
{
	(void)param;
	exit(0);
}

void	init_cam(t_scene *scene)
{
	scene->cam.dir[0] = 0;
	scene->cam.dir[1] = -1;
	scene->cam.dir[2] = 0;

	scene->cam.pos[0] = 0;
	scene->cam.pos[1] = 12;
	scene->cam.pos[2] = 0;
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
//	printf("env width %zu, env height %zu env name %s\n", env->width, env->height, env->name);
	env->width_per_height = (double)env->width / (double)env->height;
	init_env(env);
//	init_cam(&scene);
	calc(env, &scene);
	mlx_hook(env->win, KEYPRESS, KEYPRESSMASK, &ft_key_pressed, env);
	mlx_hook(env->win, KEYRELEA, KEYRELEAMASK, &ft_key_release, env);
	mlx_hook(env->win, 17, 1, &quit, NULL);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop_hook(env->mlx, recalc_img, &scene);
	mlx_loop(env->mlx);
	return (0);
}
