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

double	calc_lum_specular(struct result_hit *result_hit, float3 ray, double *lum_vect)
{
	//	double	lum_pos[3];
	double	intensite_specular;
	float3	reflection_vect;

	reflection_vect = mult_vect(result_hit->norm, 2 * scalar_product(lum_vect, result_hit->norm))
	reflection_vect = sub_vect(reflection_vect, lum_vect);
	normalize(ray); //??
	intensite_specular = scalar_product(reflection_vect, ray);
	if (intensite_specular < 0)
		return (0);
	intensite_specular = 0.7 * pow(intensite_specular, 11);
	return (intensite_specular);
}

double	calc_lum_diffuse(struct result_hit *result_hit, float3 ray, double *lum_vect)
{
	double	intensite_diffuse;

	(void)ray;
	normalize(result_hit->norm); /////////////////////////////////////////////////////////////////////////////TODO danger
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	intensite_diffuse = scalar_product(lum_vect, result_hit->norm);
	if (intensite_diffuse > 0)
		return (0);
	return (ft_abs_double(intensite_diffuse));
}

float3	calc_lum_vect(t_obj *obj, t_light *lum)
{
	float3 lum_vect;
	//	printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	sub_vect(lum_pos, lum->pos, obj->pos);
	sub_vect(lum_vect, hit_result->intersect, lum->pos);
	normalize(lum_vect);
}

size_t	calc_all_lum(t_scene *scene, struct result_hit *result_hit, float3 ray)
{
	double	intensite_diffuse;
	size_t	color;
	double	intensite_specular;
	float3	lum_vect;
	t_obj	*obj;

	intensite_specular = 0;
	intensite_diffuse = 0.1;

	obj = result_hit->obj;
	while (i < scene.lights_number)
	{
		light = scene.lights + i;
		lum_vect = calc_lum_vect(obj, light);
		/*
		**				if (obj_between_light(scene, obj, tmp, lum_vect))
		**					return (0xFF0000);
		*/
//		if (!obj_between_light(scene, obj, light, lum_vect))
//		{
			intensite_diffuse += calc_lum_diffuse(obj, ray, lum_vect);
			intensite_specular += calc_lum_specular(obj, ray, lum_vect);
//		}
		i++;
	}
	color = calc_color(intensite_diffuse, obj->color);
	color = calc_color_specular(struct *result_hit, intensite_specular, color);
	return (color);
}
