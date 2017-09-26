/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/26 18:04:36 by vcombey          ###   ########.fr       */
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

void	rot_obj(t_env *env, t_scene *s, cl_float3 (f_rot)(cl_float3, float), int sign_rot)
{
	s->objs[env->indice_obj].dirx = f_rot(s->objs[env->indice_obj].dirx, \
			TETA_ROT * sign_rot);
	s->objs[env->indice_obj].diry = f_rot(s->objs[env->indice_obj].diry, \
			TETA_ROT * sign_rot);
	s->objs[env->indice_obj].dirz = f_rot(s->objs[env->indice_obj].dirz, \
			TETA_ROT * sign_rot);
	env->obj_has_changed = 1;
}

int			recalc_img(void *scene)
{
	t_env	*env;
	t_scene	*s;

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
	if (env->rotx != 0 && env->indice_obj < s->objs_number)
		rot_obj(env, s, &rot_x, env->rotx);
	if (env->roty != 0 && env->indice_obj < s->objs_number)
		rot_obj(env, s, &rot_y, env->roty);
	if (env->rotz != 0 && env->indice_obj < s->objs_number)
		rot_obj(env, s, &rot_z, env->rotz);
	init_norm_cam_dir(&s->norm_vert, &s->norm_hor, s->cam.dir);
	return (0);
}
