#include "rt.h"
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

double	ft_abs(double u)
{
	return (u > 0 ? u : -u);
}

size_t	calc_lum(double norm_sphere[3])
{
	double	lum_pos[3];
	double	lum_vect[3];
	double	lum;

	lum_pos[0] = 2;
	lum_pos[1] = 2;
	lum_pos[2] = 1;

	ft_memset(lum_vect, 0, sizeof(double) * 3);
	sub_vect(lum_vect, norm_sphere, lum_pos);
	lum = scalar_product(lum_vect, norm_sphere);
	return ((lum - 1) * 0x00FF00);
}

size_t	throw_ray(t_cam cam, double ray[3])
{
	double	rayon;
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	double	norm_sphere[3];

	ft_memset(norm_sphere, 0, sizeof(double) * 3);
	rayon = 1;
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - rayon * rayon;

	delta = calc_delta(a, b, c);
	printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((b - sqrt(delta)) / (2 * a), (b + sqrt(delta)) / (2 * a));
	mult_vect(norm_sphere, ray, t);
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
	norm_vert[2] = 1;

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
			printf("coef %f", coef);
			ray[2] += coef * norm_vert[2];
			coef = (((double)pix_hor - (SCREEN_WIDTH / 2)) / (SCREEN_WIDTH / 2)) * 0.66 * WIDTH_PER_HEIGHT; //varie entre -0.66 et +0.66
			printf("coef %f", coef);
			ray[1] += coef * norm_hor[1];
			printf("\nray %f, %f, %f\n", ray[0], ray[1], ray[2]);
			ft_pixelput(env, pix_hor, pix_vert, throw_ray(cam, ray));
			pix_hor++;
		}
		pix_vert++;
	}
}
