/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/25 13:51:07 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	cam->dir = rot(cam->dir, TETA);
}

void	rot_left(t_cam *cam)
{
	cam->dir = rot(cam->dir, -TETA);
}

static void	rot_arround_left(t_cam *cam)
{
	cam->pos = rot(cam->pos, -TETA * 3);
	cam->dir = rot(cam->dir, -TETA * 3);
}

static void	rot_arround_right(t_cam *cam)
{
	cam->pos = rot(cam->pos, TETA * 3);
	cam->dir = rot(cam->dir, TETA * 3);
}

void	init_norm_cam_dir(cl_float3 *norm_vert, cl_float3 *norm_hor, cl_float3 dir)
{
	dir = NORMALIZE(dir);
//	printf("dir %f, %f, %f\n", dir.x, dir.y,dir.z); 
	*norm_hor = rot(dir, -M_PI / 2);
	*norm_vert =  (cl_float3){.x = 0, .y = 0, .z = 1};
	/*
**		if (dir.y != 0)
**		{
**			norm_hor->z = 0;
**			norm_hor->x = sqrt(dir.y * dir.y / (dir.x * dir.x + dir.y * dir.y));
**			norm_hor->y = -dir.x / dir.y * norm_hor->x;
**			if (norm_hor->y < 0)
**				norm_hor->y *= -1;
**		}
**		else if (dir.x != 0)
**		{
**			norm_hor->z = 0;
**			norm_hor->y = sqrt(dir.x * dir.x / (dir.x * dir.x + dir.y * dir.y));
**			if (norm_hor->y < 0)
**				norm_hor->y *= -1;
**			norm_hor->x = -dir.y / dir.x * norm_hor->y;
**		}
**		*norm_hor = normalize(*norm_hor);
**		*norm_vert = vectorial_product(*norm_hor, dir);
**		*norm_vert = normalize(*norm_vert);
*/
//	printf("hor %f, %f, %f\n", norm_hor->x, norm_hor->y,norm_hor->z); 
//	printf("vert %f, %f, %f\n", norm_vert->x, norm_vert->y,norm_vert->z); 
}

#define TETA_ROT 0.01

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
		rot_arround_left(&s->cam);
	if (env->key_t)
		rot_arround_right(&s->cam);
	if (env->rotx != 0)
	{
		s->objs[env->indice_obj].dir = rot_x(s->objs[env->indice_obj].dir, TETA_ROT * env->rotx);//segf
		env->obj_has_changed = 1;
		printf("%f, %f, %f", s->objs[env->indice_obj].dir.x, s->objs[env->indice_obj].dir.y, s->objs[env->indice_obj].dir.z);
	}
	if (env->roty != 0)
	{
		s->objs[env->indice_obj].dir = rot_y(s->objs[env->indice_obj].dir, TETA_ROT * env->roty);//segf
		env->obj_has_changed = 1;
	}
	if (env->rotz != 0)
	{
		s->objs[env->indice_obj].dir = rot_z(s->objs[env->indice_obj].dir, TETA_ROT * env->rotz);//segf
		env->obj_has_changed = 1;
	}

	else
		init = 0;
	init_norm_cam_dir(&s->norm_vert, &s->norm_hor, s->cam.dir);
//	printf("camdir %f, %f, %f\n", s->cam.dir.x, s->cam.dir.y, s->cam.dir.z);
//	printf("campos %f, %af, %f\n", s->cam.pos.x, s->cam.pos.y, s->cam.pos.z);
	return (0);
}
