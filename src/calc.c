#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

void	calc_pixel(t_env *env)
{
	(void)env;
}

size_t	calc_lum(double intersect[3], double norm[3])
{
	double	lum_pos[3];
	double	lum_vect[3];
	double	lum;
	size_t intensite_color;

	lum_pos[0] = 3;
	lum_pos[1] = 1;
	lum_pos[2] = 1;

	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum_vect, intersect, lum_pos);
	normalize(lum_vect);
	normalize(norm);
	//printf("\nintersect x %f, y %f, z %f\n", intersect[0], intersect[1], intersect[2]);
//	intersectalize(intersect); // pk intersect-sphere n est pas de intersecte rayon ?
	lum = scalar_product(lum_vect, norm);
	/*
**		if (lum > 0)
**			return (0x001000);
*/
	lum = ft_abs_double(lum);
	//		printf("lum %f\n", lum);
	intensite_color = lum * 255;
	//		printf("intensite_color %zu\n", intensite_color);
	if (intensite_color < 10)
		intensite_color = 10;
	intensite_color <<= 16;
	return (intensite_color);
}

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

size_t	calc_sphere(t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	dist;
	double	intersect_sphere[3];

	ft_memset(intersect_sphere, 0, sizeof(double) * 3);
	rayon = 1;
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - rayon * rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	mult_vect(intersect_sphere, ray, t);
	dist = norme_carre(intersect_sphere);
	add_vect(intersect_sphere, intersect_sphere, cam.pos);
	return (calc_lum(intersect_sphere, intersect_sphere));
}

void	calc(t_env *env, t_scene *scene)
{
	t_cam	cam;
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];
	size_t	pix_vert;
	size_t	pix_hor;

	(void)ray;
	(void)scene;
	cam.pos[0] = 3;
	cam.pos[1] = 0;
	cam.pos[2] = 0;

	cam.dir[0] = -1;
	cam.dir[1] = 0;
	cam.dir[2] = 0;

	ray[0] = -1;
	ray[1] = 0;
	ray[2] = 0;

	norm_vert[0] = 0;
	norm_vert[1] = 0;
	norm_vert[2] = -1;

	norm_hor[0] = 0;
	norm_hor[1] = 1;
	norm_hor[2] = 0;

	pix_vert = 0;
	pix_hor = 0;

	while (pix_vert < SCREEN_HEIGHT)
	{

		pix_hor = 0;
		while (pix_hor < SCREEN_WIDTH)
		{
		
			ray[0] = -0.66;
			ray[1] = 0;
			ray[2] = 0;

			coef = (((double)pix_vert - ((double)env->height / 2)) / ((double)env->height / 2)) * 0.66; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[2] += coef * norm_vert[2];
			coef = (((double)pix_hor - ((double)env->width / 2)) / ((double)env->width / 2)) * 0.66 * env->width_per_height; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[1] += coef * norm_hor[1];
			//printf("\nray %f, %f, %f\n", ray[0], ray[1], ray[2]);
			double	hit_sphere = calc_sphere(cam, ray);

			if (hit_sphere > 0)
				ft_pixelput(env, pix_hor, pix_vert, hit_sphere);
			else
				ft_pixelput(env, pix_hor, pix_vert, calc_plan(cam, ray));
			pix_hor++;
		}
		pix_vert++;
	}
}
