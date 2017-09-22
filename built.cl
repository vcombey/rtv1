#ifndef RT_CL_H
# define RT_CL_H
typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
}					t_point;

typedef struct		s_cam
{
	float3			dir;
	float3			pos;
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
	int				type;
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
	int				objs_number;
	t_light			*lights;
	int				lights_number;
}					t_scene;

struct		s_result_hit
{
	double			dist;
	double			t;
	float3			norm; //contient le vecteur normal a la surface
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

# define SPHERE 0
# define CONE 1
# define PLAN 2
# define CYLINDRE 3
# define NULL ((void *)0)
/*
**	void	calc(t_env *env, t_scene *scene);
**	
**	double	calc_delta(double a, double b, double c);
**	double	ft_min(double u, double v);
**	void	mult_vect(float3 res, float3 v, double t);
**	void	div_vect(float3 res, float3 v, double t);
**	void	add_vect(float3 res, float3 u, float3 v);
**	void	sub_vect(float3 res, float3 u, float3 v);
**	void	cpy_vect(float3 u, float3 v);
**	double	ft_abs_double(double u);
**	double	norme_carre(float3 v);
**	double	scalar_product(float3 u, float3 v);
**	float3	normalize(float3 v);
**	void	calc_rotation_figure(float3 ray, float3 v);
**	size_t	calc_all_lum(t_scene *scene, t_obj *obj, float3 ray);
**	size_t	calc_rayon(t_scene *scene, float3 ray);
**	t_obj	*hit(t_scene *scene, double *scene_cam_pos, float3 ray);
**	size_t	obj_between_light(t_scene *scene, t_obj *obj, t_light *lum, double *lum_vect);
**	void	translate_base(float3 res, float3 scene_cam_pos, float3 obj_pos);
**	size_t	calc_dist(double t, float3 ray);
**	void	vectorial_product(float3 res, float3 u, float3 v);
*/

int	calc_rayon(t_scene scene, float3 ray);
__kernel void	calc(__global int *output, __global t_obj *objs, __global t_light *lights, t_scene scene, int height, int width, float width_per_height);
float	calc_plan(t_obj *obj, float3 pos, float3 ray);
float	calc_cone(t_obj *obj, float3 pos, float3 ray);
float	calc_cylindre(t_obj *obj, float3 pos, float3 ray);
float	ft_min_positiv(float a, float b);
float	calc_sphere(t_obj *obj, float3 pos, float3 ray);
float	calc_obj(t_obj *obj, float3 pos, float3 ray);
int	calc_dist(float t, float3 ray);
void	assign_intersect_norm_vect(t_obj *obj, float t, float3 pos, float3 ray, struct s_result_hit *output);
void	assign_norm_vect(t_obj *obj, float t, float3 pos, float3 ray, struct s_result_hit *output);
int		hit(t_scene scene, float3 ray, struct s_result_hit *output);
int	calc_color(float coef_lum, int color);
int	calc_color_specular(float coef_lum, int color);
float	calc_lum_specular(struct s_result_hit *result_hit, float3 ray, float3 lum_vect);
float	calc_lum_diffuse(struct s_result_hit *result_hit, float3 ray, float3 lum_vect);
float3	calc_lum_vect(float3 intersect, t_light *lum);
int	calc_all_lum(t_scene scene, struct s_result_hit *result_hit, float3 ray);
float	calc_delta(float a, float b, float c);
float	ft_min(float u, float v);
float	ft_abs_float(float u);
float	norme_carre(float3 v);
float	scalar_product(float3 u, float3 v);
float3	NORMALIZE(float3 v);
float3	mult_vect( float3 v, float t);
float3	div_vect(float3 v, float t);
float3	add_vect(float3 u, float3 v);
float3	cpy_vect(float3 u, float3 v);
float3	sub_vect(float3 u, float3 v);
float3	vectorial_product(float3 u, float3 v);
#endif
int	calc_rayon(t_scene scene, float3 ray)
{
	struct s_result_hit *result_hit;

	if (hit(scene, ray, result_hit))
		return (calc_all_lum(scene, result_hit, ray));
	return (0);
}

__kernel void	calc(__global int *output, __global t_obj *objs, __global t_light *lights, t_scene scene, int height, int width, float width_per_height)
{
	float3	ray;
	float	coef;
	float3	norm_vert;
	float3	norm_hor;

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

	int	pix_vert;
	int	pix_hor;
	int		i =  get_global_id(0);
	pix_hor = i % width;
	pix_vert = i / width;

	ray.x = scene.cam.dir.x;
	ray.y = scene.cam.dir.y;
	ray.z = scene.cam.dir.z;

	coef = (((float)pix_vert - ((float)height / 2)) / ((float)height / 2)) * 0.3; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.z += -coef * norm_vert.z;
	coef = (((float)pix_hor - ((float)width / 2)) / ((float)width / 2)) * 0.3 * width_per_height; //varie entre -0.66 et +0.66
	//printf("coef %f\n", coef);
	ray.y += coef * norm_hor.y;
	//printf("\nray %f, %f, %f\n", ray.x, ray.y, ray.z);
	output[i] = calc_rayon(scene, ray);
}
float	calc_plan(t_obj *obj, float3 pos, float3 ray)
{
	float	t;
	float	diviseur;
	/*
**		float	obj->dir[3];
**	
**		obj->dir.x = 1;
**		obj->dir.y = 1;
**		obj->dir.z = 1;
*/
	diviseur = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
	if (ft_abs_float(diviseur) < 0.01)
		return (0);
	t = pos.x * obj->dir.x + pos.y * obj->dir.y + pos.z * obj->dir.z;
	t = -t / diviseur;

	if (t < 0.001)
		return (0);

	return (t);
}

float	calc_cone(t_obj *obj, float3 pos, float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;
	float	alpha = 0.7;
	float	tan_alpha_carre = tan(alpha) * tan(alpha);

//	calc_rotation_figure(ray, obj->dir);
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

float	calc_cylindre(t_obj *obj, float3 pos, float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;
	float	coef_1;
	float	coef_2;
	float	coef_div;

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

float	ft_min_positiv(float a, float b)
{
	if (a < 0 && b > 0)
		return (b);
	if (a > 0 && b < 0)
		return (a);
	return (ft_min(a, b));
}

float	calc_sphere(t_obj *obj, float3 pos, float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;

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

float	calc_obj(t_obj *obj, float3 pos, float3 ray)
{

	if (obj->type == SPHERE)
		return (calc_sphere(obj, pos, ray));
	if (obj->type == PLAN)
		return (calc_plan(obj, pos, ray));
	if (obj->type == CONE)
		return (calc_cone(obj, pos, ray));
	if (obj->type == CYLINDRE)
		return (calc_cylindre(obj, pos, ray));
	return (0);
}
int	calc_dist(float t, float3 ray)
{
	float3	cam_to_obj;
	int	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	if (dist < 0.1)
		return (0);
	return (dist);
}

void	assign_intersect_norm_vect(t_obj *obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	cpy_vect(output->norm, output->intersect); // cpy dans obj norm
	output->intersect = add_vect(output->intersect, obj->pos);
}

void	assign_norm_vect(t_obj *obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	(void)pos;
	(void)ray;
	(void)t;
	if (obj->type == PLAN)
		output->norm = obj->dir;
}

int		hit(t_scene scene, float3 ray, struct s_result_hit *output)
{
	int	dist;
	float3	pos_translated;
	float	t;
	int	i = 0;
	t_obj	*obj;

	output->obj = NULL;
	output->dist = (int)-1;
	while (i < scene.objs_number)
	{
		obj = scene.objs + i;
		pos_translated = sub_vect(scene.cam.pos, obj->pos);
		t = calc_obj(obj, pos_translated, ray);
		dist = calc_dist(t, ray);
		if (dist != 0 && dist < output->dist)
		{
			output->dist = dist;
			output->t = t;
			output->obj = obj;
			assign_intersect_norm_vect(obj, t, pos_translated, ray, output);
			assign_norm_vect(obj, t, pos_translated, ray, output);
		}
		i++;
	}
	if (output->obj == NULL)
		return (0);
	return (1);
}
int	calc_color(float coef_lum, int color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(coef_lum * (color >> 16));
	if (r > 255)
		r = 255;
	r <<= 16;
	g = (int)(coef_lum * ((color & 0xFF00) >> 8));
	if (g > 255)
		g = 255;
	g <<= 8;
	b = coef_lum * (color & 0xFF);
	if (b > 255)
		b = 255;
	return (r + g + b);
}

int	calc_color_specular(float coef_lum, int color)
{
	int	r;
	int	g;
	int	b;

	coef_lum = coef_lum * 255;
	r = (int)(coef_lum + (color >> 16));
	if (r > 255)
		r = 255;
	r <<= 16;
	g = (int)(coef_lum + ((color & 0xFF00) >> 8));
	if (g > 255)
		g = 255;
	g <<= 8;
	b = coef_lum + (color & 0xFF);
	if (b > 255)
		b = 255;
	return (r + g + b);
}

float	calc_lum_specular(struct s_result_hit *result_hit, float3 ray, float3 lum_vect)
{
	//	float	lum_pos[3];
	float	intensite_specular;
	float3	reflection_vect;

	reflection_vect = mult_vect(result_hit->norm, 2 * scalar_product(lum_vect, result_hit->norm));
	reflection_vect = sub_vect(reflection_vect, lum_vect);
	NORMALIZE(ray); //??
	intensite_specular = scalar_product(reflection_vect, ray);
	if (intensite_specular < 0)
		return (0);
	intensite_specular = 0.7 * pow(intensite_specular, 11);
	return (intensite_specular);
}

float	calc_lum_diffuse(struct s_result_hit *result_hit, float3 ray, float3 lum_vect)
{
	float	intensite_diffuse;

	(void)ray;
	NORMALIZE(result_hit->norm); /////////////////////////////////////////////////////////////////////////////TODO danger
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	intensite_diffuse = scalar_product(lum_vect, result_hit->norm);
	if (intensite_diffuse > 0)
		return (0);
	return (ft_abs_float(intensite_diffuse));
}

float3	calc_lum_vect(float3 intersect, t_light *lum)
{
	float3 lum_vect;
	//	printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	sub_vect(lum_pos, lum->pos, obj->pos);
	lum_vect = sub_vect(intersect, lum->pos);
	NORMALIZE(lum_vect);
	return (lum_vect);
}

int	calc_all_lum(t_scene scene, struct s_result_hit *result_hit, float3 ray)
{
	float	intensite_diffuse;
	int	color;
	float	intensite_specular;
	float3	lum_vect;
	t_light	*light;
	int		i;

	intensite_specular = 0;
	intensite_diffuse = 0.1;

	while (i < scene.lights_number)
	{
		light = scene.lights + i;
		lum_vect = calc_lum_vect(result_hit->intersect, light);
		/*
		**				if (obj_between_light(scene, obj, tmp, lum_vect))
		**					return (0xFF0000);
		*/
//		if (!obj_between_light(scene, obj, light, lum_vect))
//		{
			intensite_diffuse += calc_lum_diffuse(result_hit, ray, lum_vect);
			intensite_specular += calc_lum_specular(result_hit, ray, lum_vect);
//		}
		i++;
	}
	color = calc_color(intensite_diffuse, result_hit->obj->color);
	color = calc_color_specular(intensite_specular, color);
	return (color);
}
float	calc_delta(float a, float b, float c)
{
	return (b * b - 4 * a * c);
}

float	ft_min(float u, float v)
{
	return (u < v ? u : v);
}

float	ft_abs_float(float u)
{
	return (u > 0 ? u : -u);
}
float	norme_carre(float3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float	scalar_product(float3 u, float3 v)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

float3	NORMALIZE(float3 v)
{
	return (div_vect(v, sqrt(norme_carre(v))));
}
float3	mult_vect( float3 v, float t)
{
	float3	res;

	res.x = v.x * t;
	res.y = v.y * t;
	res.z = v.z * t;
	return (res);
}

float3	div_vect(float3 v, float t)
{
	float3	res;

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
