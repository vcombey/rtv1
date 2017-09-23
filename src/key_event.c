#include "rt.h"
#include "math.h"
#include "stdlib.h"
#include <mlx.h>
#include <stdio.h>
#include "libft.h"
#define TETA 0.02

void	mv_up(t_cam *cam)
{
	cam->pos.x += cam->dir.x * 0.4;
	cam->pos.y += cam->dir.y * 0.4;
}

void	mv_down(t_cam *cam)
{
	cam->pos.x -= cam->dir.x * 0.4;
	cam->pos.y -= cam->dir.y * 0.4;
}

void	rot_right(t_cam *cam)
{
	double old_posx;
	old_posx = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(TETA) - cam->dir.y * sin(TETA);
	cam->dir.y = old_posx * sin(TETA) + cam->dir.y * cos(TETA);
	printf("camdir %f, %f, %f\n", cam->dir.x, cam->dir.y,cam->dir.z);
}

void	rot_left(t_cam *cam)
{

	double old_posx;
	old_posx = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(-TETA) - cam->dir.y * sin(-TETA);
	cam->dir.y = old_posx * sin(-TETA) + cam->dir.y * cos(-TETA);
	printf("camdir %f, %f, %f\n", cam->dir.x, cam->dir.y,cam->dir.z);
}

static void	rot_arround_left(t_cam *cam)
{
	double old_posx;
	old_posx = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(-TETA) - cam->dir.y * sin(-TETA);
	cam->dir.y = old_posx * sin(-TETA) + cam->dir.y * cos(-TETA);
	old_posx = cam->pos.x;
	cam->pos.x = cam->pos.x * cos(-TETA) - cam->pos.y * sin(-TETA);
	cam->pos.y = old_posx * sin(-TETA) + cam->pos.y * cos(-TETA);
	printf("campos %f, %f, %f\n", cam->pos.x, cam->pos.y,cam->pos.z);
}

static void	rot_arround_right(t_cam *cam)
{
	double old_posx;
	old_posx = cam->dir.x;
	cam->dir.x = cam->dir.x * cos(TETA) - cam->dir.y * sin(TETA);
	cam->dir.y = old_posx * sin(TETA) + cam->dir.y * cos(TETA);
	old_posx = cam->pos.x;
	cam->pos.x = cam->pos.x * cos(TETA) - cam->pos.y * sin(TETA);
	cam->pos.y = old_posx * sin(TETA) + cam->pos.y * cos(TETA);
	printf("campos %f, %f, %f\n", cam->pos.x, cam->pos.y,cam->pos.z);
}

cl_float3	vectorial_product(cl_float3 u, cl_float3 v)
{
	cl_float3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}

double	norme_carre(cl_float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

cl_float3	div_vect(cl_float3 v, double t)
{
	cl_float3	res;

	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

cl_float3	normalize(cl_float3 v)
{
	return (div_vect(v, sqrt(norme_carre(v))));
}

void	init_norm_cam_dir(cl_float3 *norm_vert, cl_float3 *norm_hor, cl_float3 dir)
{
	dir = normalize(dir);
	printf("dir %f, %f, %f\n", dir.x, dir.y,dir.z); 
	if (dir.y != 0)
	{
		norm_hor->z = 0;
		norm_hor->x = sqrt(dir.y * dir.y / (dir.x * dir.x + dir.y * dir.y));
		norm_hor->y = -dir.x / dir.y * norm_hor->x;
		if (norm_hor->y < 0)
			norm_hor->y *= -1;
	}
	else if (dir.x != 0)
	{
		norm_hor->z = 0;
		norm_hor->y = sqrt(dir.x * dir.x / (dir.x * dir.x + dir.y * dir.y));
		if (norm_hor->y < 0)
			norm_hor->y *= -1;
		norm_hor->x = -dir.y / dir.x * norm_hor->y;
	}
	*norm_hor = normalize(*norm_hor);
	*norm_vert = vectorial_product(*norm_hor, dir);
	*norm_vert = normalize(*norm_vert);
	printf("hor %f, %f, %f\n", norm_hor->x, norm_hor->y,norm_hor->z); 
	printf("vert %f, %f, %f\n", norm_vert->x, norm_vert->y,norm_vert->z); 
}

int			recalc_img(void *scene)
{
	t_env	*env;
	t_scene	*s;
	int		init;

	init = 1;
	s = (t_scene *)scene;
	env = singleton_env();
	if (env->up)
		mv_up(&s->cam);
	if (env->down)
		mv_down(&s->cam);
	if (env->left)
		rot_right(&s->cam);
	if (env->right)
		rot_left(&s->cam);
	if (env->key_r)
		rot_arround_left( &s->cam);
	if (env->key_t)
		rot_arround_right(&s->cam);
	else
		init = 0;
	init_norm_cam_dir(&s->norm_vert, &s->norm_hor, s->cam.dir);
//	printf("camdir %f, %f, %f\n", s->cam.dir.x, s->cam.dir.y, s->cam.dir.z);
//	printf("campos %f, %f, %f\n", s->cam.pos.x, s->cam.pos.y, s->cam.pos.z);
	return (0);
}
