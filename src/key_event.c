#include "rt.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#define TETA 0.20

static void	ft_turn(t_env *env, t_cam *cam)
{
	double old_dirx;

	if (env->left)
	{
		old_dirx = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(TETA) - cam->dir.y * sin(TETA);
		cam->dir.y = old_dirx * sin(TETA) + cam->dir.y * cos(TETA);
	}
	if (env->right)
	{
		old_dirx = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(-TETA) - cam->dir.y * sin(-TETA);
		cam->dir.y = old_dirx * sin(-TETA) + cam->dir.y * cos(-TETA);
	}
}

void	mv_up(t_env *env, t_cam *cam)
{
	if (env->up)
	{
			env->starty--;
		cam->pos.x += cam->dir.x * 0.4;
		cam->pos.y += cam->dir.y * 0.4;
	}
}

void	mv_down(t_env *env, t_cam *cam)
{
	if (env->down)
	{
		env->starty++;
		cam->pos.x -= cam->dir.x * 0.4;
		cam->pos.y -= cam->dir.y * 0.4;
	}
}

void	rot_right(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->right)
	{
		env->startx++;
		old_posx = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(TETA) - cam->dir.y * sin(TETA);
		cam->dir.y = old_posx * sin(TETA) + cam->dir.y * cos(TETA);
		printf("camdir %f, %f, %f\n", cam->dir.x, cam->dir.y,cam->dir.z);
	}
}

 void	rot_left(t_env *env, t_cam *cam)
{

	double old_posx;
	if (env->left)
	{

		env->startx--;
		old_posx = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(-TETA) - cam->dir.y * sin(-TETA);
		cam->dir.y = old_posx * sin(-TETA) + cam->dir.y * cos(-TETA);
		printf("camdir %f, %f, %f\n", cam->dir.x, cam->dir.y,cam->dir.z);
	}
}

static void	rot_arround_left(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->key_r)
	{
		old_posx = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(-TETA) - cam->dir.y * sin(-TETA);
		cam->dir.y = old_posx * sin(-TETA) + cam->dir.y * cos(-TETA);
		old_posx = cam->pos.x;
		cam->pos.x = cam->pos.x * cos(-TETA) - cam->pos.y * sin(-TETA);
		cam->pos.y = old_posx * sin(-TETA) + cam->pos.y * cos(-TETA);
		printf("campos %f, %f, %f\n", cam->pos.x, cam->pos.y,cam->pos.z);
	}
}

static void	rot_arround_right(t_env *env, t_cam *cam)
{
	double old_posx;
	if (env->key_t)
	{
		old_posx = cam->dir.x;
		cam->dir.x = cam->dir.x * cos(TETA) - cam->dir.y * sin(TETA);
		cam->dir.y = old_posx * sin(TETA) + cam->dir.y * cos(TETA);
		old_posx = cam->pos.x;
		cam->pos.x = cam->pos.x * cos(TETA) - cam->pos.y * sin(TETA);
		cam->pos.y = old_posx * sin(TETA) + cam->pos.y * cos(TETA);
		printf("campos %f, %f, %f\n", cam->pos.x, cam->pos.y,cam->pos.z);
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
//	printf("camdir %f, %f, %f\n", s->cam.dir.x, s->cam.dir.y, s->cam.dir.z);
//	printf("campos %f, %f, %f\n", s->cam.pos.x, s->cam.pos.y, s->cam.pos.z);
	ft_memset(env->ptr, 0x00, env->width * env->height * 4);
	calc(env, scene);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}
