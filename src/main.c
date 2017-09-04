#include <mlx.h>
#include "rt.h"
#include "libft.h"

t_env	*singleton_env()
{
	static t_env	env;

	return (&env);
}

int		main(int ac, char **av)
{
	t_env	*env;
	t_scene	scene;


		if (ac != 2)
			fatal ("usage: rt_v1 <filename>");

	(void)ac;
	(void)av;
	parse_file(av[1], &scene);
	env = singleton_env();
	init_env(env);
	calc(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}
