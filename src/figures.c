#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_plan(t_cam cam, double ray[3])
{
	double	t;
	double	dist;
	double	norm_plan[3];
	double	intersect_plan[3];
	double	diviseur;

	norm_plan[0] = 1;
	norm_plan[1] = 1;
	norm_plan[2] = 0;

	diviseur = norm_plan[0] * ray[0] + norm_plan[1] * ray[1] + norm_plan[2] * ray[2];
	if (ft_abs_double(diviseur) < 0.000001)
		return (0);
	t = cam.pos[0] * norm_plan[0] + cam.pos[1] * norm_plan[1] + cam.pos[2] * norm_plan[2];
	t = -t / diviseur;
	mult_vect(intersect_plan, ray, t);
	dist = norme_carre(intersect_plan);
	add_vect(intersect_plan, intersect_plan, cam.pos);

	//printf("\nintersect_plan x %f, y %f, z %f\n", intersect_plan[0], intersect_plan[1], intersect_plan[2]);
	if (intersect_plan[2] < 0)
		intersect_plan[2] = -intersect_plan[2];
//  return (0xFF0000);
	return (calc_lum(intersect_plan, norm_plan));
}

size_t	calc_cone(t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	dist;
	double	intersect_cone[3];
	double	alpha = 0.7;
	double	tan_alpha_carre = tan(alpha) * tan(alpha);

	ft_memset(intersect_cone, 0, sizeof(double) * 3);
	rayon = 1;
	a = ray[0] * ray[0] + ray[1] * ray[1] - ray[2] * ray[2] * tan_alpha_carre;
	b = 2 * cam.pos[0] * ray[0] + 2 * cam.pos[1] * ray[1] - 2 * cam.pos[2] * ray[2] * tan_alpha_carre;
	c = cam.pos[0] * cam.pos[0] + cam.pos[1] * cam.pos[1] - cam.pos[2] * cam.pos[2] * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));

	mult_vect(intersect_cone, ray, t);
	dist = norme_carre(intersect_cone);
	add_vect(intersect_cone, intersect_cone, cam.pos);

	if (intersect_cone[2] < 0)
		intersect_cone[2] = -intersect_cone[2];
//  return (0xFF0000);
	return (calc_lum(intersect_cone, intersect_cone));
}

size_t	calc_cylindre(t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	dist;
	double	intersect_cylindre[3];

	ft_memset(intersect_cylindre, 0, sizeof(double) * 3);
	rayon = 1;
	a = ray[0] * ray[0] + ray[1] * ray[1];
	b = 2 * cam.pos[0] * ray[0] + 2 * cam.pos[1] * ray[1];
	c = cam.pos[0] * cam.pos[0] + cam.pos[1] * cam.pos[1] - rayon * rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));

	mult_vect(intersect_cylindre, ray, t);
	dist = norme_carre(intersect_cylindre);
	add_vect(intersect_cylindre, intersect_cylindre, cam.pos);

	intersect_cylindre[2] = 0;
//  return (0xFF0000);
	return (calc_lum(intersect_cylindre, intersect_cylindre));
}

size_t	calc_sphere(t_obj *obj, t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	size_t	dist;

	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	rayon = 1;
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - rayon * rayon;

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
/*
**			if (ft_strequ(tmp->name, "plan"))
**				tmp->f = &calc_plan;
**			if (ft_strequ(tmp->name, "cone"))
**				tmp->f = &calc_cone;
**			if (ft_strequ(tmp->name, "cylindre"))
**				tmp->f = &calc_cylindre;
*/
		tmp = tmp->next;
	}
}
