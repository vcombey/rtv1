#ifndef RT_H
# define RT_H

#include <string.h>
#include <mlx.h>
#include <OpenCL/opencl.h>

typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct		s_cam
{
	double			dir[3];
	double			pos[3];
}					t_cam;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	size_t			width;
	size_t			height;
	size_t			up;
	size_t			down;
	size_t			right;
	size_t			left;
	size_t			key_shift_left;
	size_t			key_shift_right;
	size_t			key_r;
	size_t			key_t;
	size_t			rot_right;
	size_t			rot_left;
	double			width_per_height;
	char			*ptr;
	int				bpp;
	int				size_line;
	int				endian;
	char			*name;
}					t_env;

typedef struct		s_obj
{
	char			*name;
	double			*pos;
	double			*dir;
	size_t			color;
	double			alpha;
	double			rayon;
	struct s_obj	*next;
	double			*intersect;
	double			*norm;
	double			(*f)(struct s_obj *, double[3], double[3]);
}					t_obj;

typedef struct		s_light
{
	double			*pos;
	struct s_light	*next;
}					t_light;

typedef struct		s_yaml
{
	size_t			tab;
	char			*key;
	char			*value;
}					t_yaml;

typedef struct		s_scene
{
	char			*name;
	double			rot[3];
	size_t			width;
	size_t			height;
	t_cam			cam;
	t_obj			*objs;
	t_light			*lights;
}					t_scene;

typedef struct	s_func
{
	char		*key;
	size_t		(*f)(t_yaml *, size_t, t_scene *k, size_t);
}				t_func;

# define KEY_ESCAPE 53
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_UP 126
# define KEY_B 11
# define KEY_PAD_SUB 78
# define KEY_PAD_ADD 69
# define KEY_R 15
# define KEY_Z 6
# define KEY_H 4
# define KEY_S 1
# define KEY_SHIFT_LEFT 257
# define KEY_SHIFT_RIGHT 258
# define KEY_R 15
# define KEY_T 17
# define KEYPRESSMASK (1l << 0)
# define KEYRELEAMASK (1l << 1)
# define KEYPRESS 2
# define KEYRELEA 3
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 800
# define WIDTH_PER_HEIGHT SCREEN_WIDTH/SCREEN_HEIGHT

t_env				*env(void);
int					init_env(t_env *env);
void	calc(t_env *env, t_scene *scene);

void				ft_pixelput(t_env *env, int x, int y, int color);

double	calc_delta(double a, double b, double c);
double	ft_min(double u, double v);
double	ft_abs_double(double u);
void	mult_vect(double res[3], double v[3], double t);
void	div_vect(double res[3], double v[3], double t);
void	add_vect(double res[3], double u[3], double v[3]);
void	sub_vect(double res[3], double u[3], double v[3]);
void	cpy_vect(double u[3], double v[3]);
double	norme_carre(double v[3]);
double	scalar_product(double u[3], double v[3]);
void	normalize(double v[3]);
void	parse_file(char *filename, t_scene *scene);
void	get_coordinates(double	res[3], char *value);
void	parse_scene(t_yaml *lines, size_t len, t_scene *scene);
size_t	get_name(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_windows_size(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_camera(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_all_objects(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_cone(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_cylindre(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_plan(t_yaml *lines, size_t i, t_scene *scene, size_t len);
size_t	get_sphere(t_yaml *lines, size_t i, t_scene *scene, size_t len);
void	ft_obj_add(t_obj *new_node, t_obj **first);
double	get_rayon(char *value);
double	get_hexa(char *value);
void	ft_obj_add(t_obj *new_node, t_obj **first);
t_obj	*ft_new_obj(void);
void	assign_obj_func(t_scene *scene);
size_t	get_light(t_yaml *lines, size_t i, t_scene *scene, size_t len);
void	calc_rotation_figure(double ray[3], double v[3]);
size_t	calc_all_lum(t_scene *scene, t_obj *obj, double ray[3]);
size_t	calc_rayon(t_scene *scene, double ray[3]);
t_obj	*hit(t_scene *scene, double *scene_cam_pos, double ray[3]);
size_t	obj_between_light(t_scene *scene, t_obj *obj, t_light *lum, double *lum_vect);
void	translate_base(double res[3], double scene_cam_pos[3], double obj_pos[3]);
size_t	calc_dist(double t, double ray[3]);
void	vectorial_product(double res[3], double u[3], double v[3]);

int		ft_key_pressed(int keycode, void *env);
int		ft_key_release(int keycode, void *env);
t_env	*singleton_env();
int			recalc_img(void *scene);

void	init_scene(t_scene *scene);
int	quit(void *param);

const char *getErrorString(cl_int error);

#endif
#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

size_t	calc_rayon(t_scene *scene, double ray[3])
{
	t_obj	*shortest_obj;

	shortest_obj = hit(scene, scene->cam.pos, ray);
	if (shortest_obj)
		return (calc_all_lum(scene, shortest_obj, ray));
	return (0);
}

void	init_norm_cam_dir(double norm_vert[3], double norm_hor[3], double dir[3])
{
	normalize(dir);
	printf("dir %f, %f, %f\n", dir[0], dir[1],dir[2]); 
	if (dir[1] != 0)
	{
		norm_hor[2] = 0;
		norm_hor[0] = sqrt(dir[1] * dir[1] / (dir[0] * dir[0] + dir[1] * dir[1]));
		norm_hor[1] = -dir[0] / dir[1] * norm_hor[0];
		if (norm_hor[1] < 0)
			norm_hor[1] *= -1;
	}
	else if (dir[0] != 0)
	{
		norm_hor[2] = 0;
		norm_hor[1] = sqrt(dir[0] * dir[0] / (dir[0] * dir[0] + dir[1] * dir[1]));
		if (norm_hor[1] < 0)
			norm_hor[1] *= -1;
		norm_hor[0] = -dir[1] / dir[0] * norm_hor[1];
	}
	normalize(norm_hor);
	vectorial_product(norm_vert, norm_hor, dir);
	normalize(norm_vert);
	printf("hor %f, %f, %f\n", norm_hor[0], norm_hor[1],norm_hor[2]); 
	printf("vert %f, %f, %f\n", norm_vert[0], norm_vert[1],norm_vert[2]); 
}

void	calc(t_env *env, t_scene *scene)
{
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];
	size_t	pix_vert;
	size_t	pix_hor;

	assign_obj_func(scene);
	(void)scene;
	normalize(scene->cam.dir);

	init_norm_cam_dir(norm_vert, norm_hor, scene->cam.dir);

	/*
**	 	norm_vert[0] = 0;
**	 	norm_vert[1] = 0;
**	 	norm_vert[2] = 1;
**	
**	 	norm_hor[0] = -1;
**	 	norm_hor[1] = 0;
**	 	norm_hor[2] = 0;
**	
*/

	pix_vert = 0;
	pix_hor = 0;

	while (pix_vert < SCREEN_HEIGHT)
	{

		pix_hor = 0;
		while (pix_hor < SCREEN_WIDTH)
		{
			ray[0] = scene->cam.dir[0];
			ray[1] = scene->cam.dir[1];
			ray[2] = scene->cam.dir[2];

			coef = (((double)pix_vert - ((double)env->height / 2)) / ((double)env->height / 2)) * 0.3; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[2] += -coef * norm_vert[2];
			coef = (((double)pix_hor - ((double)env->width / 2)) / ((double)env->width / 2)) * 0.3 * env->width_per_height; //varie entre -0.66 et +0.66
			//printf("coef %f\n", coef);
			ray[1] += coef * norm_hor[1];
			//printf("\nray %f, %f, %f\n", ray[0], ray[1], ray[2]);
			ft_pixelput(env, pix_hor, pix_vert, calc_rayon(scene, ray));
			pix_hor++;
		}
		pix_vert++;
	}
}
static void		ft_pixelput(__global char *output, int x, int y, int color, size_t height, size_t width)
{
	int				i;
	int				dest;
	unsigned int	new_color;

	if (y < 0 || x < 0)
		return ;
	dest = y * 100 + x * (32 / 8);
	if ((int)(height * width * (32 / 8)) <= dest)
		return ;
	if (dest < 0)
		return ;
	i = -1;
	while (++i < 32 / 8)
	{
		output[dest + i] = new_color >> (i * 8) & 0xFF;
	}
}


__kernel void	calc(
__global int *output, 
size_t height,
size_t width)
{
	int		i =  get_global_id(0);
	output[i] = i % 255;
}
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
#include <mlx.h>
#include "rt.h"

void				ft_pixelput(t_env *env, int x, int y, int color)
{
	int				i;
	int				dest;
	unsigned int	new_color;

	if (y < 0 || x < 0)
		return ;
	new_color = mlx_get_color_value(env->mlx, color);
	dest = y * env->size_line + x * (env->bpp / 8);
	if ((SCREEN_HEIGHT * SCREEN_WIDTH * (env->bpp / 8)) <= dest)
		return ;
	if (dest < 0)
		return ;
	i = -1;
	while (++i < env->bpp / 8)
	{
		env->ptr[dest + i] = new_color >> (i * 8) & 0xFF;
	}
}
#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int		ft_str_is_clear(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isblanckspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	get_coordinates(double	res[3], char *value)
{
	char	*coord;

	coord = value;
	res[0] = strtod(coord, &coord);
	res[1] = strtod(coord, &coord);
	res[2] = strtod(coord, &coord);
	if (!ft_str_is_clear(coord))
		fatal("invalid coordinates");
}

double	get_rayon(char *value)
{
	double	res;

	res = strtod(value, &value);
	if (!ft_str_is_clear(value))
		fatal("invalid valueinates");
	return (res);
}

double	get_hexa(char *value)
{
	double	res;

	res = strtod(value, &value);
	if (!ft_str_is_clear(value))
		fatal("invalid valueinates");
	return (res);
}
#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

void	translate_base(double res[3], double scene_cam_pos[3], double obj_pos[3])
{
	ft_memset(res, 0, sizeof(double) * 3);
	sub_vect(res, scene_cam_pos, obj_pos);
}

size_t	calc_dist(double t, double ray[3])
{
	double	cam_to_obj[3];
	size_t	dist;

	mult_vect(cam_to_obj, ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj *obj, double t, double pos[3], double ray[3])
{
	mult_vect(obj->intersect, ray, t);
	add_vect(obj->intersect, obj->intersect, pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	add_vect(obj->intersect, obj->intersect, obj->pos);
}

void	assign_norm_vect(t_obj *obj, double t, double pos[3], double ray[3])
{
	(void)pos;
	(void)ray;
	(void)t;
	if (ft_strequ(obj->name, "plan"))
		cpy_vect(obj->norm, obj->dir); // cpy dans obj norm
}

t_obj	*hit(t_scene *scene, double *scene_cam_pos, double ray[3])
{
	t_obj	*tmp;
	t_obj	*shortest_obj;
	size_t	min_dist;
	size_t	dist;
	double	pos[3];
	double	t;

	shortest_obj = NULL;
	min_dist = (size_t)-1;
	tmp = scene->objs;
	while (tmp)
	{
		translate_base(pos, scene_cam_pos, tmp->pos);
		t = tmp->f(tmp, pos, ray);
		dist = calc_dist(t, ray);
		assign_intersect_norm_vect(tmp, t, pos, ray);
		assign_norm_vect(tmp, t, pos, ray);
		if (dist != 0 && dist < min_dist)
		{
			shortest_obj = tmp;
			min_dist = dist;
		}
		tmp = tmp->next;
	}
	return (shortest_obj);
}
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
//	printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
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
		/*
**				if (obj_between_light(scene, obj, tmp, lum_vect))
**					return (0xFF0000);
*/

	
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

size_t	calc_all_lum(t_scene *scene, t_obj *obj)
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

#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

t_obj	*ft_new_obj(void)
{
	t_obj	*new;
	new = ft_memalloc(sizeof(t_obj));
	new->pos = ft_memalloc(sizeof(double) * 3);
	new->dir = ft_memalloc(sizeof(double) * 3);
	new->intersect = ft_memalloc(sizeof(double) * 3);
	new->norm = ft_memalloc(sizeof(double) * 3);
	return (new);
}

void	ft_obj_add(t_obj *new_node, t_obj **first)
{
	new_node->next = *first;
	*first = new_node;
}
#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

int		hit_ombre(double intersect[3], t_scene *scene, double *scene_cam_pos, double ray[3], t_obj *obj)
{
	t_obj	*tmp;
	t_obj	*shortest_obj;
	size_t	min_dist;
	size_t	dist;
	double	pos[3];
	double	t;
	double	min_t;

	shortest_obj = NULL;
	min_dist = (size_t)-1;
	tmp = scene->objs;
	while (tmp)
	{
		translate_base(pos, scene_cam_pos, tmp->pos);
		t = tmp->f(tmp, pos, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < min_dist && tmp != obj)
		{
			min_t = t;
			shortest_obj = tmp;
			min_dist = dist;
		}
		tmp = tmp->next;
	}
	if (!shortest_obj)
		return (0);
	mult_vect(intersect, ray, t);
	add_vect(intersect, intersect, pos);
	add_vect(intersect, intersect, shortest_obj->pos);
	return (1);
}

size_t	obj_between_light(t_scene *scene, t_obj *obj, t_light *lum, double *lum_vect)
{
	double	hit_obj_intersect[3];
	double	obj_obj[3];
	double	obj_light[3];
	double	lum_vect_cpy[3];

	mult_vect(lum_vect_cpy, lum_vect, -1);
	if (!hit_ombre(hit_obj_intersect, scene, obj->intersect, lum_vect_cpy, obj))
		return (0);
	sub_vect(obj_obj, obj->intersect, hit_obj_intersect);
	sub_vect(obj_light, obj->intersect, lum->pos);
	if (norme_carre(obj_obj) < norme_carre(obj_light))
	{
//		printf("ombre\n");
		return (1);
	}
//	printf("\nobj_intersect x %f\ny %f\nz %f\n", obj->intersect[0], obj->intersect[1], obj->intersect[2]);
//	printf("\nhit_obj_intersect x %f\ny %f\nz %f\n", hit_obj_intersect[0], hit_obj_intersect[1], hit_obj_intersect[2]);
	return (0);
}

double	calc_delta(double a, double b, double c)
{
	return (b * b - 4 * a * c);
}

double	ft_min(double u, double v)
{
	return (u < v ? u : v);
}

double	ft_abs_double(double u)
{
	return (u > 0 ? u : -u);
}
#include <math.h>
#include "rt.h"

double	norme_carre(double v[3])
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

double	scalar_product(double u[3], double v[3])
{
	return (v[0] * u[0] + v[1] * u[1] + v[2] * u[2]);
}

void	normalize(double v[3])
{
	div_vect(v, v, sqrt(norme_carre(v)));
}
#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

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

void	add_vect(double res[3], double u[3], double v[3])
{
	res[0] = u[0] + v[0];
	res[1] = u[1] + v[1];
	res[2] = u[2] + v[2];
}

void	cpy_vect(double u[3], double v[3])
{
	u[0] = v[0];
	u[1] = v[1];
	u[2] = v[2];
}

void	sub_vect(double res[3], double u[3], double v[3])
{
	res[0] = u[0] - v[0];
	res[1] = u[1] - v[1];
	res[2] = u[2] - v[2];
}

void	vectorial_product(double res[3], double u[3], double v[3])
{
	res[0] = u[1] * v[2] - u[2] * v[1];
	res[1] = u[2] * v[0] - u[0] * v[2];
	res[2] = u[0] * v[1] - u[1] * v[0];
}
#include "rt.h"
#include "libft.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

static double	mat_mult_coef(double a[3][3], double b[3][3], size_t a_line, size_t b_col)
{
	size_t	i;
	double	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i][b_col];
		i++;
	}
	return (res);
}

void	mat_mult(double res[3][3], double a[3][3], double b[3][3])
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i][j] = mat_mult_coef(a, b, i, j);
			j++;
		}
		i++;
	}
}

static double	mat_mult_vect_coef(double a[3][3], double b[3], size_t a_line)
{
	size_t	i;
	double	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i];
		i++;
	}
	return (res);
}

void	mat_mult_vect(double res[3], double a[3][3], double x[3])
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		res[i] = mat_mult_vect_coef(a, x, i);
		i++;
	}
}

void	calc_rotation_figure(double ray[3], double v[3])
{
//	normalize(v);
	double	mat_x[3][3] = {
		{1, 0, 0},
		{0, v[2], -v[1]},
		{0, v[1], v[2]},
	};
	double	mat_y[3][3] = {
		{v[2], 0, -v[0]},
		{0, 1, 0},
		{v[0], 0, v[2]},
	};
	double	mat_z[3][3] = {
		{v[2], -v[0], 0},
		{v[0], v[2], 0},
		{0, 0, 1},
	};
	double	res[3][3];
	mat_mult(res, mat_y, mat_x);
	mat_mult_vect(ray, res, ray);
	(void)mat_y;
	(void)mat_z;
}
