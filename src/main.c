#include <mlx.h>
#include "rt.h"

t_env	*singleton_env()
{
	static t_env	env;

	return (&env);
}

int		main()
{
	t_env	*env;

	env = singleton_env();
	init_env(env);
	calc(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}
