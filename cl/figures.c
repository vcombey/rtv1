#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

double	calc_plan(t_obj *obj, float3 pos, float3 ray)
{
	double	t;
	double	diviseur;
	/*
**		double	obj->dir[3];
**	
**		obj->dir.x = 1;
**		obj->dir.y = 1;
**		obj->dir.z = 1;
*/
	diviseur = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
	if (ft_abs_double(diviseur) < 0.01)
		return (0);
	t = pos.x * obj->dir.x + pos.y * obj->dir.y + pos.z * obj->dir.z;
	t = -t / diviseur;

	if (t < 0.001)
		return (0);

	return (t);
}

double	calc_cone(t_obj *obj, float3 pos, float3 ray)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	alpha = 0.7;
	double	tan_alpha_carre = tan(alpha) * tan(alpha);

//	calc_rotation_figure(ray, obj->dir);
	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	a = ray.x * ray.x + ray.y * ray.y - ray.z * ray.z * tan_alpha_carre;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * pos.z * ray.z * tan_alpha_carre;
	c = pos.x * pos.x + pos.y * pos.y - pos.z * pos.z * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	return (t);
}

double	calc_cylindre(t_obj *obj, float3 pos, float3 ray)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	coef_1;
	double	coef_2;
	double	coef_div;

//	calc_rotation_figure(ray, obj->dir);

	coef_div = obj->dir.x * obj->dir.x + obj->dir.y * obj->dir.y + obj->dir.z * obj->dir.z;
	if (coef_div == 0)
		return (0);
	coef_1 = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
	coef_2 = obj->dir.x * pos.x + obj->dir.y * pos.y + obj->dir.z * pos.z;
	a = ray.x * ray.x + ray.y * ray.y - coef_1 * coef_1 / coef_div;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * coef_1 * coef_2 / coef_div;
	c = pos.x * pos.x + pos.y * pos.y - obj->rayon * obj->rayon - coef_2 * coef_2 / coef_div;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	if (t < 0.1)
		return (0);
	return (t);
}

double	ft_min_positiv(double a, double b)
{
	if (a < 0 && b > 0)
		return (b);
	if (a > 0 && b < 0)
		return (a);
	return (ft_min(a, b));
}

double	calc_sphere(t_obj *obj, float3 pos, float3 ray)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;

	a = norme_carre(ray);
	b = 2 * scalar_product(ray, pos);
	c = norme_carre(pos) - obj->rayon * obj->rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0);
	t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	if (t < 0)
		return (0);
	return (t);
}

double	calc_obj_func(t_obj *obj, float3 pos, float3 ray)
{

	if (obj->type == SPHERE)
		return (calc_sphere(obj, pos, ray));
	if (obj->type == PLAN)
		return (calc_plan(obj, pos, ray));
	if (obj->type == CONE)
		return (calc_cone(obj, pos, ray));
	if (obj->type == CYLINDRE)
		return (calc_cylindre(obj, pos, ray));
}
