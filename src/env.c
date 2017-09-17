#include "rt.h"
#include "libft.h"
#include <unistd.h>
#include <mlx.h>

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

int		init_env(t_env *env)
{
	env->win = NULL;
	env->img = NULL;
	env->mlx = NULL;
	if (!(env->mlx = mlx_init()))
		fatal("mlx problem");
	if (!(env->win = mlx_new_window(env->mlx, env->width,
	env->height, env->name)))
		fatal("mlx problem");
	if (!(env->img = mlx_new_image(env->mlx, env->width,
	env->height)))
		fatal("mlx problem");
	env->ptr = mlx_get_data_addr(env->img, &env->bpp, &env->size_line,
	&env->endian);
	return (0);
}
