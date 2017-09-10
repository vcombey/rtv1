#include "rt.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include "libft.h"

static void	ft_turn(t_env *env, t_cam cam)
{
	double old_dirx;

	if (env->left)
	{
		old_dirx = cam.dir[0];
		cam.dir[0] = cam.dir[0] * cos(0.04) - cam.dir[1] * sin(0.04);
		cam.dir[1] = old_dirx * sin(0.04) + cam.dir[1] * cos(0.04);
	}
	if (env->right)
	{
		old_dirx = cam.dir[0];
		cam.dir[0] = cam.dir[0] * cos(-0.04) - cam.dir[1] * sin(-0.04);
		cam.dir[1] = old_dirx * sin(-0.04) + cam.dir[1] * cos(-0.04);
	}
}

static void	mv_up(t_env *env, t_cam cam)
{
	if (env->up)
	{
		cam.pos[0] += cam.dir[0] * 0.1;
		cam.pos[1] += cam.dir[1] * 0.1;
	}
}

static void	mv_down(t_env *env, t_cam cam)
{
	if (env->down)
	{
		cam.pos[0] -= cam.dir[0] * 0.1;
		cam.pos[1] -= cam.dir[1] * 0.1;
	}
}

int			recalc_img(void *scene)
{
	t_env	*env;

	env = singleton_env();
	mv_up(env, ((t_scene*)scene)->cam);
	mv_down(env, ((t_scene*)scene)->cam);
	ft_turn(env, ((t_scene*)scene)->cam);
	ft_memset(env->ptr, 0x00, env->width * env->height * 4);
	calc(env, scene);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
