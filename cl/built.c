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
	float3			dir[3];
	float3			pos[3];
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
	struct s_cl		*cl;
	size_t			startx;
	size_t			starty;
}					t_env;

typedef struct		s_obj
{
	int				*type;
	float3		pos;
	float3		dir;
	size_t			color;
	double			alpha;
	double			rayon;
}					t_obj;

typedef struct		s_light
{
	float3			pos;
}					t_light;

typedef struct		s_scene
{
	char			*name;
	float3		rot;
	size_t			width;
	size_t			height;
	t_cam			cam;
	t_obj			*objs;
	t_light			*lights;
}					t_scene;

struct		s_result_hit
{
	double			dist;
	double			t;
	float3			norm_vect; //contient le vecteur normal a la surface
	float3			intersect; //contient le point dans le plan non translate d'intersection
	t_obj			*obj; //pointeur sur lobjet intersecter
};

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

void	calc(t_env *env, t_scene *scene);

double	calc_delta(double a, double b, double c);
double	ft_min(double u, double v);
void	mult_vect(float3 res, float3 v, double t);
void	div_vect(float3 res, float3 v, double t);
void	add_vect(float3 res, float3 u, float3 v);
void	sub_vect(float3 res, float3 u, float3 v);
void	cpy_vect(float3 u, float3 v);
double	ft_abs_double(double u);
double	norme_carre(float3 v);
double	scalar_product(float3 u, float3 v);
void	normalize(float3 v);
void	calc_rotation_figure(float3 ray, float3 v);
size_t	calc_all_lum(t_scene *scene, t_obj *obj, float3 ray);
size_t	calc_rayon(t_scene *scene, float3 ray);
t_obj	*hit(t_scene *scene, double *scene_cam_pos, float3 ray);
size_t	obj_between_light(t_scene *scene, t_obj *obj, t_light *lum, double *lum_vect);
void	translate_base(float3 res, float3 scene_cam_pos, float3 obj_pos);
size_t	calc_dist(double t, float3 ray);
void	vectorial_product(float3 res, float3 u, float3 v);

#endif
size_t	calc_rayon(t_scene scene, float3 ray)
{
	t_obj	*shortest_obj;
	struct result_hit *output;

	shortest_obj = hit(scene, ray, output);
	if (shortest_obj)
		return (calc_all_lum(scene, shortest_obj, ray));
	return (0);
}

void	init_norm_cam_dir(float3 *norm_vert, float3 *norm_hor, float3 dir)
{
	normalize(dir);
	printf("dir %f, %f, %f\n", dir.x, dir.y,dir.z); 
	if (dir.y != 0)
	{
		norm_hor.z = 0;
		norm_hor.x = sqrt(dir.y * dir.y / (dir.x * dir.x + dir.y * dir.y));
		norm_hor.y = -dir.x / dir.y * norm_hor.x;
		if (norm_hor.y < 0)
			norm_hor.y *= -1;
	}
	else if (dir.x != 0)
	{
		norm_hor.z = 0;
		norm_hor.y = sqrt(dir.x * dir.x / (dir.x * dir.x + dir.y * dir.y));
		if (norm_hor.y < 0)
			norm_hor.y *= -1;
		norm_hor.x = -dir.y / dir.x * norm_hor.y;
	}
	normalize(norm_hor);
	vectorial_product(norm_vert, norm_hor, dir);
	normalize(norm_vert);
	printf("hor %f, %f, %f\n", norm_hor.x, norm_hor.y,norm_hor.z); 
	printf("vert %f, %f, %f\n", norm_vert.x, norm_vert.y,norm_vert.z); 
}

void	calc(
		t_scene scene
		__global t_obj *objs
		__global t_light *lights
		__global int *output,
		size_t height
		size_t width
		size_t width_per_height)
{
	double	ray[3];
	double	coef;
	double	norm_vert[3];
	double	norm_hor[3];

	normalize(scene.cam.dir);
	init_norm_cam_dir(norm_vert, norm_hor, scene.cam.dir);

	/*
**	 	norm_vert.x = 0;
**	 	norm_vert.y = 0;
**	 	norm_vert.z = 1;
**	
**	 	norm_hor.x = -1;
**	 	norm_hor.y = 0;
**	 	norm_hor.z = 0;
**	
*/

	size_t	pix_vert;
	size_t	pix_hor;
	int		i =  get_global_id(0);
	pix_hor = i % width;
	pix_vert = i / width;

	ray.x = scene.cam.dir.x;
	ray.y = scene.cam.dir.y;
	ray.z = scene.cam.dir.z;

	coef = (((double)pix_vert - ((double)height / 2)) / ((double)height / 2)) * 0.3; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.z += -coef * norm_vert.z;
	coef = (((double)pix_hor - ((double)width / 2)) / ((double)width / 2)) * 0.3 * width_per_height; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.y += coef * norm_hor.y;
	//printf("\nray %f, %f, %f\n", ray.x, ray.y, ray.z);
	output[i] = calc_rayon(scene, ray);
}
double	calc_plan(t_obj *obj, float3 pos, float3 ray)
{
	double	t;
	double	diviseur;
	/*
**		double	obj->dir[3];
**	
**		obj->dir.x = 1;
**		obj->dir.y = 1;
**		obj->dir.z = 1;
*/
	diviseur = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
	if (ft_abs_double(diviseur) < 0.01)
		return (0);
	t = pos.x * obj->dir.x + pos.y * obj->dir.y + pos.z * obj->dir.z;
	t = -t / diviseur;

	if (t < 0.001)
		return (0);

	return (t);
}

double	calc_cone(t_obj *obj, float3 pos, float3 ray)
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
	a = ray.x * ray.x + ray.y * ray.y - ray.z * ray.z * tan_alpha_carre;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * pos.z * ray.z * tan_alpha_carre;
	c = pos.x * pos.x + pos.y * pos.y - pos.z * pos.z * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	return (t);
}

double	calc_cylindre(t_obj *obj, float3 pos, float3 ray)
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

	coef_div = obj->dir.x * obj->dir.x + obj->dir.y * obj->dir.y + obj->dir.z * obj->dir.z;
	if (coef_div == 0)
		return (0);
	coef_1 = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
	coef_2 = obj->dir.x * pos.x + obj->dir.y * pos.y + obj->dir.z * pos.z;
	a = ray.x * ray.x + ray.y * ray.y - coef_1 * coef_1 / coef_div;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * coef_1 * coef_2 / coef_div;
	c = pos.x * pos.x + pos.y * pos.y - obj->rayon * obj->rayon - coef_2 * coef_2 / coef_div;

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

double	calc_sphere(t_obj *obj, float3 pos, float3 ray)
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

double	calc_obj(t_obj *obj, float3 pos, float3 ray)
{

	if (obj->type == SPHERE)
		return (calc_sphere(obj, pos, ray));
	if (obj->type == PLAN)
		return (calc_plan(obj, pos, ray));
	if (obj->type == CONE)
		return (calc_cone(obj, pos, ray));
	if (obj->type == CYLINDRE)
		return (calc_cylindre(obj, pos, ray));
}
size_t	calc_dist(double t, float3 ray)
{
	float3	cam_to_obj;
	size_t	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj *obj, double t, float3 pos, float3 ray, struct result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	output->intersect = add_vect(output->intersect, obj->pos);
}

void	assign_norm_vect(t_obj *obj, double t, float3 pos, float3 ray)
{
	(void)pos;
	(void)ray;
	(void)t;
	if (obj->type == PLAN)
		cpy_vect(obj->norm, obj->dir); // cpy dans obj norm
}

int		hit(t_scene scene, float3 ray, t_obj *shortest_obj, struct result_hit *output)
{
	size_t	min_dist;
	size_t	dist;
	float3	pos_tranlated;
	double	t;
	size_t	i = 0;
	t_obj	*obj;

	output->obj = NULL;
	output->dist = (size_t)-1;
	while (i < scene.objs_number)
	{
		obj = scene.objs + i;
		pos_translated = sub_vect(scene.cam.pos, obj_pos);
		t = calc_obj(obj, pos_translated, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < output->dist)
		{
			output->dist = dist;
			output->t = t;
			output->obj = obj;
			assign_intersect_norm_vect(tmp, t, translated_pos, ray, output);
			assign_norm_vect(tmp, t, pos, ray, output);
		}
		i++;
	}
	if (output->obj == NULL)
		return (0);
	return (1);
}
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
int		hit_ombre(float3 intersect, t_scene *scene, double *scene_cam_pos, float3 ray, t_obj *obj)
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
//	printf("\nobj_intersect x %f\ny %f\nz %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
//	printf("\nhit_obj_intersect x %f\ny %f\nz %f\n", hit_obj_intersect.x, hit_obj_intersect.y, hit_obj_intersect.z);
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
double	norme_carre(float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	scalar_product(float3 u, float3 v)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

float3	normalize(float3 v)
{
	return (div_vect(v, sqrt(norme_carre(v))));
}
float3	mult_vect( float3 v, double t)
{
	float3	res;

	res.x = v.x * t;
	res.y = v.y * t;
	res.z = v.z * t;
	return (res);
}

float3	div_vect(float3 v, double t)
{
	float3	res;

	if (t == 0)
		return ;
	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

float3	add_vect(float3 u, float3 v)
{
	float3	res;

	res.x = u.x + v.x;
	res.y = u.y + v.y;
	res.z = u.z + v.z;
	return (res);
}

float3	cpy_vect(float3 u, float3 v)
{
	float3	res;

	u.x = v.x;
	u.y = v.y;
	u.z = v.z;
	return (res);
}

float3	sub_vect(float3 u, float3 v)
{
	float3	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	res.z = u.z - v.z;
	return (res);
}

float3	vectorial_product(float3 u, float3 v)
{
	float3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}
static double	mat_mult_coef(float3 a[3], float3 b[3], size_t a_line, size_t b_col)
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

void	mat_mult(float3 res[3], float3 a[3], float3 b[3])
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

static double	mat_mult_vect_coef(float3 a[3], float3 b, size_t a_line)
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

void	mat_mult_vect(float3 res, float3 a[3], float3 x)
{
	size_t	i;

	i = 0;
	while (i < 3)
	{
		res[i] = mat_mult_vect_coef(a, x, i);
		i++;
	}
}

void	calc_rotation_figure(float3 ray, float3 v)
{
//	normalize(v);
	double	mat_x[3][3] = {
		{1, 0, 0},
		{0, v.z, -v.y},
		{0, v.y, v.z},
	};
	double	mat_y[3][3] = {
		{v.z, 0, -v.x},
		{0, 1, 0},
		{v.x, 0, v.z},
	};
	double	mat_z[3][3] = {
		{v.z, -v.x, 0},
		{v.x, v.z, 0},
		{0, 0, 1},
	};
	double	res[3][3];
	mat_mult(res, mat_y, mat_x);
	mat_mult_vect(ray, res, ray);
	(void)mat_y;
	(void)mat_z;
}
