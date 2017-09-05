#include <mlx.h>
#include "rt.h"
#include "libft.h"
#include <stdio.h>

t_env	*singleton_env()
{
	static t_env	env;

	return (&env);
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
	parse_file(av[1], &scene);
	env = singleton_env();
	env->width = scene.width;
	env->height = scene.height;
	env->name = "rt";
	printf("env width %zu, env height %zu env name %s\n", env->width, env->height, env->name);
	env->width_per_height = (double)env->width / (double)env->height;
	printf("coucou\n");
	init_env(env);
	printf("coucou\n");
	calc(env, &scene);
	printf("coucou\n");
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}
