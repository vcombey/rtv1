#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_plan(t_obj *obj, t_cam cam, double ray[3])
{
	double	t;
	double	dist;
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
	t = cam.pos[0] * obj->dir[0] + cam.pos[1] * obj->dir[1] + cam.pos[2] * obj->dir[2];
	t = -t / diviseur;
	if (t < 0)
		return (0);
	mult_vect(obj->intersect, ray, t);
	dist = norme_carre(obj->intersect);
	add_vect(obj->intersect, obj->intersect, cam.pos);
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
	/*
**		if (obj->intersect[2] < 0)
**			obj->intersect[2] = -obj->intersect[2];
*/
//  return (0xFF0000);
	cpy_vect(obj->norm, obj->dir); // cpy dans obj norm
	return (dist);
}

size_t	calc_cone(t_obj *obj, t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	dist;
	double	alpha = 0.7;
	double	tan_alpha_carre = tan(alpha) * tan(alpha);

	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	rayon = 1;
	a = ray[0] * ray[0] + ray[1] * ray[1] - ray[2] * ray[2] * tan_alpha_carre;
	b = 2 * cam.pos[0] * ray[0] + 2 * cam.pos[1] * ray[1] - 2 * cam.pos[2] * ray[2] * tan_alpha_carre;
	c = cam.pos[0] * cam.pos[0] + cam.pos[1] * cam.pos[1] - cam.pos[2] * cam.pos[2] * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));

	mult_vect(obj->intersect, ray, t);
	dist = norme_carre(obj->intersect);
	add_vect(obj->intersect, obj->intersect, cam.pos);
	if (obj->intersect[2] < 0)
		obj->intersect[2] = -obj->intersect[2];
//  return (0xFF0000);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	return (dist);
	//return (calc_lum(obj->intersect, obj->intersect));
}

size_t	calc_cylindre(t_obj *obj, t_cam cam, double ray[3])
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	dist;

//	calc_rotation_figure(ray, obj->dir);

	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	a = ray[0] * ray[0] + ray[1] * ray[1];
	b = 2 * cam.pos[0] * ray[0] + 2 * cam.pos[1] * ray[1];
	c = cam.pos[0] * cam.pos[0] + cam.pos[1] * cam.pos[1] - obj->rayon * obj->rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	mult_vect(obj->intersect, ray, t);
	dist = norme_carre(obj->intersect);
	add_vect(obj->intersect, obj->intersect, cam.pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	obj->norm[2] = 0;
	return (dist);
	//return (calc_lum(intersect_cylindre, intersect_cylindre));
}

size_t	calc_sphere(t_obj *obj, t_cam cam, double ray[3])
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	size_t	dist;

	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - obj->rayon * obj->rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	mult_vect(obj->intersect, ray, t);
	dist = norme_carre(obj->intersect);
	add_vect(obj->intersect, obj->intersect, cam.pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	return (dist);
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
