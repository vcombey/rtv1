#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

double	calc_delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

void	calc_pixel(t_env *env)
{
	(void)env;
}

double	norme_carre(double v[3])
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

double	scalar_product(double u[3], double v[3])
{
	return (v[0] * u[0] + v[1] * u[1] + v[2] * u[2]);
}

void	mult_vect(double res[3], double v[3], double t)
{
	res[0] = v[0] * t;
	res[1] = v[1] * t;
	res[2] = v[2] * t;
}

void	div_vect(double res[3], double v[3], double t)
{
	if (t == 0)
		return ;
	res[0] = v[0] / t;
	res[1] = v[1] / t;
	res[2] = v[2] / t;
}

void	normalize(double v[3])
{
	div_vect(v, v, sqrt(norme_carre(v)));
}

void	add_vect(double res[3], double u[3], double v[3])
{
	res[0] = u[0] + v[0];
	res[1] = u[1] + v[1];
	res[2] = u[2] + v[2];
}

void	sub_vect(double res[3], double u[3], double v[3])
{
	res[0] = u[0] - v[0];
	res[1] = u[1] - v[1];
	res[2] = u[2] - v[2];
}

double	ft_min(double u, double v)
{
	return (u < v ? u : v);
}

double	ft_abs_double(double u)
{
	return (u > 0 ? u : -u);
}

size_t	calc_lum(double norm_sphere[3])
{
	double	lum_pos[3];
	double	lum_vect[3];
	double	lum;
	size_t intensite_color;

	lum_pos[0] = 3;
	lum_pos[1] = 1;
	lum_pos[2] = 1;

	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum_vect, norm_sphere, lum_pos);
	normalize(lum_vect);
	printf("\nnorm_sphere x %f, y %f, z %f\n", norm_sphere[0], norm_sphere[1], norm_sphere[2]);
//	normalize(norm_sphere); // pk norm-sphere n est pas de norme rayon ?
	lum = scalar_product(lum_vect, norm_sphere);
	if (lum > 0)
		return (0x001000);
	lum = ft_abs_double(lum);
			printf("lum %f\n", lum);
	intensite_color = lum * 255;
			printf("intensite_color %zu\n", intensite_color);
	if (intensite_color < 10)
		intensite_color = 10;
	intensite_color <<= 8;
	return (intensite_color);
}

size_t	calc_plan(t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	dist;
	double	norm_cone[3];
	double	alpha = 0.7;
	double	tan_alpha_carre = tan(alpha) * tan(alpha);

	ft_memset(norm_cone, 0, sizeof(double) * 3);
	rayon = 1;
	a = ray[0] * ray[0] + ray[1] * ray[1] - ray[2] * ray[2] * tan_alpha_carre;
	b = 2 * cam.pos[0] * ray[0] + 2 * cam.pos[1] * ray[1] - 2 * cam.pos[2] * ray[2] * tan_alpha_carre;
	c = cam.pos[0] * cam.pos[0] + cam.pos[1] * cam.pos[1] - cam.pos[2] * cam.pos[2] * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));

	mult_vect(norm_cone, ray, t);
	dist = norme_carre(norm_cone);
	add_vect(norm_cone, norm_cone, cam.pos);

	if (norm_cone[2] < 0)
		norm_cone[2] = -norm_cone[2];
//  return (0xFF0000);
	return (calc_lum(norm_cone));
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
	double	norm_cone[3];
	double	alpha = 0.7;
	double	tan_alpha_carre = tan(alpha) * tan(alpha);

	ft_memset(norm_cone, 0, sizeof(double) * 3);
	rayon = 1;
	a = ray[0] * ray[0] + ray[1] * ray[1] - ray[2] * ray[2] * tan_alpha_carre;
	b = 2 * cam.pos[0] * ray[0] + 2 * cam.pos[1] * ray[1] - 2 * cam.pos[2] * ray[2] * tan_alpha_carre;
	c = cam.pos[0] * cam.pos[0] + cam.pos[1] * cam.pos[1] - cam.pos[2] * cam.pos[2] * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));

	mult_vect(norm_cone, ray, t);
	dist = norme_carre(norm_cone);
	add_vect(norm_cone, norm_cone, cam.pos);

	if (norm_cone[2] < 0)
		norm_cone[2] = -norm_cone[2];
//  return (0xFF0000);
	return (calc_lum(norm_cone));

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
	double	norm_sphere[3];

	ft_memset(norm_sphere, 0, sizeof(double) * 3);
	rayon = 1;
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - rayon * rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	mult_vect(norm_sphere, ray, t);
	dist = norme_carre(norm_sphere);
	add_vect(norm_sphere, norm_sphere, cam.pos);
	return (calc_lum(norm_sphere));
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
	double	norm_sphere[3];

	ft_memset(norm_sphere, 0, sizeof(double) * 3);
	rayon = 1;
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - rayon * rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	mult_vect(norm_sphere, ray, t);
	dist = norme_carre(norm_sphere);
	add_vect(norm_sphere, norm_sphere, cam.pos);
	return (calc_lum(norm_sphere));
}

void	calc(t_env *env)
{
	t_cam	cam;
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];
	size_t	pix_vert;
	size_t	pix_hor;

	(void)ray;
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

			coef = (((double)pix_vert - (SCREEN_HEIGHT / 2)) / (SCREEN_HEIGHT / 2)) * 0.66; //varie entre -0.66 et +0.66
			//printf("coef %f", coef);
			ray[2] += coef * norm_vert[2];
			coef = (((double)pix_hor - (SCREEN_WIDTH / 2)) / (SCREEN_WIDTH / 2)) * 0.66 * WIDTH_PER_HEIGHT; //varie entre -0.66 et +0.66
			//printf("coef %f", coef);
			ray[1] += coef * norm_hor[1];
			//printf("\nray %f, %f, %f\n", ray[0], ray[1], ray[2]);
			ft_pixelput(env, pix_hor, pix_vert, calc_sphere(cam, ray));
			pix_hor++;
		}
		pix_vert++;
	}
}
