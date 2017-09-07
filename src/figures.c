#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

double	calc_plan(t_obj *obj, double pos[3], double ray[3])
{
	double	t;
	double	diviseur;
	/*
**		double	obj->dir[3];
**	
**		obj->dir[0] = 1;
**		obj->dir[1] = 1;
**		obj->dir[2] = 1;
*/
	diviseur = obj->dir[0] * ray[0] + obj->dir[1] * ray[1] + obj->dir[2] * ray[2];
	if (ft_abs_double(diviseur) < 0.01)
		return (0);
	t = pos[0] * obj->dir[0] + pos[1] * obj->dir[1] + pos[2] * obj->dir[2];
	t = -t / diviseur;

	if (t < 0.001)
		return (0);

	return (t);
}

double	calc_cone(t_obj *obj, double pos[3], double ray[3])
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
	a = ray[0] * ray[0] + ray[1] * ray[1] - ray[2] * ray[2] * tan_alpha_carre;
	b = 2 * pos[0] * ray[0] + 2 * pos[1] * ray[1] - 2 * pos[2] * ray[2] * tan_alpha_carre;
	c = pos[0] * pos[0] + pos[1] * pos[1] - pos[2] * pos[2] * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	return (t);
}

double	calc_cylindre(t_obj *obj, double pos[3], double ray[3])
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

	coef_div = obj->dir[0] * obj->dir[0] + obj->dir[1] * obj->dir[1] + obj->dir[2] * obj->dir[2];
	if (coef_div == 0)
		return (0);
	coef_1 = obj->dir[0] * ray[0] + obj->dir[1] * ray[1] + obj->dir[2] * ray[2];
	coef_2 = obj->dir[0] * pos[0] + obj->dir[1] * pos[1] + obj->dir[2] * pos[2];
	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	a = ray[0] * ray[0] + ray[1] * ray[1] - coef_1 * coef_1 / coef_div;
	b = 2 * pos[0] * ray[0] + 2 * pos[1] * ray[1] - 2 * coef_1 * coef_2 / coef_div;
	c = pos[0] * pos[0] + pos[1] * pos[1] - obj->rayon * obj->rayon - coef_2 * coef_2 / coef_div;

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

double	calc_sphere(t_obj *obj, double pos[3], double ray[3])
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

void	assign_obj_func(t_scene *scene)
{
	t_obj	*tmp;

	tmp = scene->objs;
	while (tmp)
	{
		if (ft_strequ(tmp->name, "sphere"))
			tmp->f = &calc_sphere;
		if (ft_strequ(tmp->name, "plan"))
			tmp->f = &calc_plan;
		if (ft_strequ(tmp->name, "cone"))
			tmp->f = &calc_cone;
		if (ft_strequ(tmp->name, "cylindre"))
			tmp->f = &calc_cylindre;
		tmp = tmp->next;
	}
}
