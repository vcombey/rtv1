#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_color(double coef_lum, size_t color)
{
	size_t	r;
	size_t	g;
	size_t	b;

	r = (size_t)(coef_lum * (color >> 16));
	if (r > 255)
		r = 255;
	r <<= 16;
	g = (size_t)(coef_lum * ((color & 0xFF00) >> 8));
	if (g > 255)
		g = 255;
	g <<= 8;
	b = coef_lum * (color & 0xFF);
	if (b > 255)
		b = 255;
	return (r + g + b);
}

size_t	calc_color_specular(double coef_lum, size_t color)
{
	size_t	r;
	size_t	g;
	size_t	b;

	coef_lum = coef_lum * 255;
	r = (size_t)(coef_lum + (color >> 16));
	if (r > 255)
		r = 255;
	r <<= 16;
	g = (size_t)(coef_lum + ((color & 0xFF00) >> 8));
	if (g > 255)
		g = 255;
	g <<= 8;
	b = coef_lum + (color & 0xFF);
	if (b > 255)
		b = 255;
	return (r + g + b);
}

double	calc_lum_specular(t_obj *obj, double ray[3], double *lum_vect)
{
//	double	lum_pos[3];
	double	intensite_specular;
	double	reflection_vect[3];

	ft_memset(reflection_vect, 0, sizeof(double) * 3);
	mult_vect(reflection_vect, obj->norm, 2 * scalar_product(lum_vect, obj->norm));
	sub_vect(reflection_vect, reflection_vect, lum_vect);
	normalize(ray);
	intensite_specular = scalar_product(reflection_vect, ray);
	if (intensite_specular < 0)
		return (0);
	intensite_specular = 0.7 * pow(intensite_specular, 11);
	return (intensite_specular);
}

double	calc_lum_diffuse(t_obj *obj, double ray[3], double *lum_vect)
{
	double	intensite_diffuse;

	(void)ray;
	normalize(obj->norm);
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	intensite_diffuse = scalar_product(lum_vect, obj->norm);
	if (intensite_diffuse > 0)
		return (0);
	return (ft_abs_double(intensite_diffuse));
}

void	calc_lum_vect(double *lum_vect, t_obj *obj, t_light *lum)
{
	ft_memset(lum_vect, 0, sizeof(double) * 3);
//	sub_vect(lum_pos, lum->pos, obj->pos);
	sub_vect(lum_vect, obj->intersect, lum->pos);
	normalize(lum_vect);
}

size_t	calc_all_lum(t_scene *scene, t_obj *obj, double ray[3])
{
	t_light	*tmp;
	double	intensite_diffuse;
	size_t	color;
	double	intensite_specular;
	double	lum_vect[3];

	intensite_specular = 0;
	intensite_diffuse = 0.1;
	tmp = scene->lights;
	while (tmp)
	{
		calc_lum_vect(lum_vect, obj, tmp);
		//if (obj_between_light(scene, obj, tmp, lum_vect))
		//	return (0xFF0000);
		if (!obj_between_light(scene, obj, tmp, lum_vect))
		{
			intensite_diffuse += calc_lum_diffuse(obj, ray, lum_vect);
			intensite_specular += calc_lum_specular(obj, ray, lum_vect);
		}
		tmp = tmp->next;
	}
	color = calc_color(intensite_diffuse, obj->color);
	color = calc_color_specular(intensite_specular, color);
	return (color);
}
