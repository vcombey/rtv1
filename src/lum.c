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

double	calc_lum_specular(t_obj *obj, t_light *lum, double ray[3])
{
	double	lum_vect[3];
	double	lum_pos[3];
	double	intensite_specular;
	double	reflection_vect[3];

	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum_pos, lum->pos, obj->pos);
	sub_vect(lum_vect, obj->intersect, lum->pos);
	normalize(lum_vect);

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


double	calc_lum_diffuse(t_obj *obj, t_light *lum, double ray[3])
{
	double	lum_vect[3];
	double	lum_pos[3];
	double	intensite_diffuse;

	(void)ray;
	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum_pos, lum->pos, obj->pos);
	sub_vect(lum_vect, obj->intersect, lum_pos);
	normalize(lum_vect);
	normalize(obj->norm);
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	intensite_diffuse = scalar_product(lum_vect, obj->norm);
	if (intensite_diffuse > 0)
		return (0);
	return (ft_abs_double(intensite_diffuse));

/*
**		if (lum > 0)
**			return (0x001000);
*/
//	intensite = intensite_diffuse + intensite_specular;
	//		printf("intensite %f\n", intensite);
//	return (((size_t)(lum * (obj->color >> 16)) << 16) & (((size_t)(lum * (obj->color & 0xFF00 >> 8)) << 8) & ((size_t)(lum * (obj->color & 0xFF))));
	//		printf("intensite_obj->color %zu\n", intensite_obj->color);
}

size_t	calc_all_lum(t_scene *scene, t_obj *obj, double ray[3])
{
	t_light	*tmp;
	double	coef_lum;
	size_t	color;
	double	intensite_specular;

	(void)ray;
	intensite_specular = 0;
	coef_lum = 0.1;
	tmp = scene->lights;
	while (tmp)
	{
//		translate_base(tmp, cam.pos, scene->cam.pos);
		coef_lum += calc_lum_diffuse(obj, tmp, ray);
		intensite_specular += calc_lum_specular(obj, tmp, ray);
		tmp = tmp->next;
	}
	
/*
**			if (coef_lum > 1)
**				coef_lum = 1;
**	
*/
	color = calc_color(coef_lum, obj->color);
	color = calc_color_specular(intensite_specular, color);
	return (color);
}
