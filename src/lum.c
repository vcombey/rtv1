#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_color(double coef_lum, size_t color)
{
	size_t	intensite_lum;

	intensite_lum = (size_t)(coef_lum * (color >> 16)) << 16;
	intensite_lum += (size_t)(coef_lum * ((color & 0xFF00) >> 8)) << 8;
	intensite_lum += coef_lum * (color & 0xFF);
	return (intensite_lum);
}

double	calc_lum(t_obj *obj, t_light *lum)
{
	double	lum_vect[3];
	double	coef_lum;

	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum->pos, lum->pos, obj->pos);
	sub_vect(lum_vect, obj->intersect, lum->pos);
	normalize(lum_vect);
	normalize(obj->norm);
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	coef_lum = scalar_product(lum_vect, obj->norm);
/*
**		if (lum > 0)
**			return (0x001000);
*/
	coef_lum = ft_abs_double(coef_lum);
	//		printf("coef_lum %f\n", coef_lum);
	return (coef_lum);
//	return (((size_t)(lum * (obj->color >> 16)) << 16) & (((size_t)(lum * (obj->color & 0xFF00 >> 8)) << 8) & ((size_t)(lum * (obj->color & 0xFF))));
	//		printf("intensite_obj->color %zu\n", intensite_obj->color);
}

size_t	calc_all_lum(t_scene *scene, t_obj *obj, double ray[3])
{
	t_light	*tmp;
	double	coef_lum;

	coef_lum = 0;
	tmp = scene->lights;
	while (tmp)
	{
//		translate_base(tmp, cam.pos, scene->cam.pos);
		coef_lum += calc_lum(obj, tmp);
		tmp = tmp->next;
	}
	if (coef_lum > 1)
		coef_lum = 1;
	return (calc_color(coef_lum, obj->color));
}
