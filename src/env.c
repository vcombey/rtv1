#include "rt.h"
#include "libft.h"
#include <unistd.h>
#include <mlx.h>

int		init_env(t_env *env)
{
	env->win = NULL;
	env->img = NULL;
	env->mlx = NULL;
	if (!(env->mlx = mlx_init()))
		fatal("mlx problem");
	if (!(env->win = mlx_new_window(env->mlx, SCREEN_WIDTH,
	SCREEN_HEIGHT, "rt")))
		fatal("mlx problem");
	if (!(env->img = mlx_new_image(env->mlx, SCREEN_WIDTH,
	SCREEN_HEIGHT)))
		fatal("mlx problem");
	env->ptr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
	&env->endian);
	return (0);
}
