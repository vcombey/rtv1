/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figures.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 13:44:26 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/25 18:44:40 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

float	ft_min_positiv(float a, float b)
{
	if (a < 0 && b > 0)
		return (b);
	if (a > 0 && b < 0)
		return (a);
	return (ft_min(a, b));
}

float	calc_plan(t_obj *obj, cl_float3 pos, cl_float3 ray)
{
	float	t;
	float	diviseur;

	diviseur = obj->dirz.x * ray.x + obj->dirz.y * ray.y + obj->dirz.z * ray.z;
	if (ft_abs_float(diviseur) < 0.01)
		return (0);
	t = pos.x * obj->dirz.x + pos.y * obj->dirz.y + pos.z * obj->dirz.z;
	t = -t / diviseur;
	return (t);
}

float	calc_cone(t_obj *obj, cl_float3 pos, cl_float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;
	float	tan_alpha_carre;

	tan_alpha_carre = tan(obj->alpha) * tan(obj->alpha);
//	calc_rotation_figure(ray, obj->dirz);
	(void)obj;
	a = ray.x * ray.x + ray.y * ray.y - ray.z * ray.z * tan_alpha_carre;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * pos.z * ray.z * tan_alpha_carre;
	c = pos.x * pos.x + pos.y * pos.y - pos.z * pos.z * tan_alpha_carre;
	delta = calc_delta(a, b, c);
	if (delta < 0)
		return (0x0);
	t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	return (t);
}

float	calc_cylindre(t_obj *obj, cl_float3 pos, cl_float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;

//	calc_rotation_figure(ray, obj->dirz);
	a = ray.x * ray.x + ray.y * ray.y;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y;
	c = pos.x * pos.x + pos.y * pos.y - obj->rayon * obj->rayon;
	delta = calc_delta(a, b, c);
	if (delta < 0)
		return (0x0);
	t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	return (t);
}

float	calc_sphere(t_obj *obj, cl_float3 pos, cl_float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;

	a = norme_carre(ray);
	b = 2 * scalar_product(ray, pos);
	c = norme_carre(pos) - obj->rayon * obj->rayon;
	delta = calc_delta(a, b, c);
	if (delta < 0)
		return (0);
	t = ft_min_positiv(((-b - (sqrt(delta))) / (2 * a)), ((-b + (sqrt(delta))) / (2 * a)));
	return (t);
}

float	calc_obj(t_obj *obj, cl_float3 pos, cl_float3 ray)
{
	if (obj->type == SPHERE)
		return (calc_sphere(obj, pos, ray));
	if (obj->type == PLAN)
		return (calc_plan(obj, pos, ray));
	if (obj->type == CONE)
		return (calc_cone(obj, pos, ray));
	if (obj->type == CYLINDRE)
		return (calc_cylindre(obj, pos, ray));
	return (0);
}
