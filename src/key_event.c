#include "rt.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#define TETA 0.08

static void	ft_turn(t_env *env, t_cam *cam)
{
	double old_dirx;

	if (env->left)
	{
		old_dirx = cam->dir[0];
		cam->dir[0] = cam->dir[0] * cos(TETA) - cam->dir[1] * sin(TETA);
		cam->dir[1] = old_dirx * sin(TETA) + cam->dir[1] * cos(TETA);
	}
	if (env->right)
	{
		old_dirx = cam->dir[0];
		cam->dir[0] = cam->dir[0] * cos(-TETA) - cam->dir[1] * sin(-TETA);
		cam->dir[1] = old_dirx * sin(-TETA) + cam->dir[1] * cos(-TETA);
	}
}

static void	mv_up(t_env *env, t_cam *cam)
{
	if (env->up)
	{
		cam->pos[0] += cam->dir[0] * 0.4;
		cam->pos[1] += cam->dir[1] * 0.4;
	}
}

static void	mv_down(t_env *env, t_cam *cam)
{
	if (env->down)
	{
		cam->pos[0] -= cam->dir[0] * 0.4;
		cam->pos[1] -= cam->dir[1] * 0.4;
	}
}

static void	rot_right(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->rot_right)
	{
		old_posx = cam->dir[0];
		cam->dir[0] = cam->dir[0] * cos(TETA) - cam->dir[1] * sin(TETA);
		cam->dir[1] = old_posx * sin(TETA) + cam->dir[1] * cos(TETA);
	}
}

static void	rot_left(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->rot_left)
	{
		old_posx = cam->dir[0];
		cam->dir[0] = cam->dir[0] * cos(-TETA) - cam->dir[1] * sin(-TETA);
		cam->dir[1] = old_posx * sin(-TETA) + cam->dir[1] * cos(-TETA);
	}
}

static void	rot_arround_left(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->key_r)
	{
		rot_right(env, cam);
		old_posx = cam->pos[0];
		cam->pos[0] = cam->pos[0] * cos(-TETA) - cam->pos[1] * sin(-TETA);
		cam->pos[1] = old_posx * sin(-TETA) + cam->pos[1] * cos(-TETA);
	}
}

static void	rot_arround_right(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->key_t)
	{
		rot_left(env, cam);
		old_posx = cam->pos[0];
		cam->pos[0] = cam->pos[0] * cos(TETA) - cam->pos[1] * sin(TETA);
		cam->pos[1] = old_posx * sin(TETA) + cam->pos[1] * cos(TETA);
	}
}

int			recalc_img(void *scene)
{
	t_env	*env;
	t_scene	*s;

	s = (t_scene *)scene;
	env = singleton_env();
	mv_up(env, &s->cam);
	mv_down(env, &s->cam);
	rot_right(env, &s->cam);
	rot_left(env, &s->cam);
	rot_arround_left(env, &s->cam);
	rot_arround_right(env, &s->cam);
	ft_turn(env, &s->cam);
//	printf("camdir %f, %f, %f\n", s->cam.dir[0], s->cam.dir[1], s->cam.dir[2]);
//	printf("campos %f, %f, %f\n", s->cam.pos[0], s->cam.pos[1], s->cam.pos[2]);
	ft_memset(env->ptr, 0x00, env->width * env->height * 4);
	calc(env, scene);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
