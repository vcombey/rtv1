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
	float3			pos;
	float3			dir;
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
	float3			rot;
	int				width;
	int				height;
	float3			cam_dir;
	float3			cam_pos;
	int				objs_number;
	int				lights_number;
}					t_scene;

struct		s_result_hit
{
	float			dist;
	float			t;
	float3			norm; //contient le vecteur normal a la surface
	float3			intersect; //contient le point dans le plan non translate d'intersection
	t_obj			obj; //pointeur sur lobjet intersecter
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

int	calc_rayon(__global t_obj *objs, __global t_light *lights, t_scene scene, float3 ray);
void	debug_light(t_scene scene, __global t_light *lights);
void	debug_obj(t_scene scene,  __global t_obj *objs);
void	debug_scene(t_scene scene, __global t_obj *objs, __global t_light *lights);
__kernel void	calc(__global int *output, __global t_obj *objs, __global t_light *lights, int height, int width, float width_per_height, int objs_number, int lights_number, float3 cam_dir, float3 cam_pos, float3 norm_hor, float3 norm_vert);
float	calc_plan(t_obj *obj, float3 pos, float3 ray);
float	calc_cone(t_obj *obj, float3 pos, float3 ray);
float	calc_cylindre(t_obj *obj, float3 pos, float3 ray);
float	ft_min_positiv(float a, float b);
float	calc_sphere(t_obj *obj, float3 pos, float3 ray);
float	calc_obj(t_obj *obj, float3 pos, float3 ray);
float	calc_dist(float t, float3 ray);
void	assign_intersect_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output);
void	assign_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output);
int		hit(__global t_obj *objs, int objs_number, float3 cam_pos, float3 ray,  struct s_result_hit *result_hit);
int	calc_color(float coef_lum, int color);
int	calc_color_specular(float coef_lum, int color);
float	calc_lum_specular(struct s_result_hit *result_hit, float3 ray, float3 lum_vect);
float	calc_lum_diffuse(struct s_result_hit *result_hit, float3 ray, float3 lum_vect);
float3	calc_lum_vect(float3 intersect, t_light lum);
int	calc_all_lum(__global t_light *lights, __global t_obj *objs, t_scene scene, struct s_result_hit *result_hit, float3 ray);
int	obj_between_light(t_scene scene, __global t_obj *objs, t_light lum, float3 lum_vect, struct s_result_hit  hit_forward);
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
int	calc_rayon(__global t_obj *objs, __global t_light *lights, t_scene scene, float3 ray)
{
	struct s_result_hit result_hit;

	if (hit(objs, scene.objs_number, scene.cam_pos, ray, &result_hit))
	{
		//return (0xFF);
		return (calc_all_lum(lights, objs, scene, &result_hit, ray));
	}
	return (0);
}

void	debug_light(t_scene scene, __global t_light *lights)
{
	int		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene.lights_number)
	{
		printf("pos %f, %f, %f\n", lights[i].pos.x, lights[i].pos.y, lights[i].pos.z);
		i++;
	}
}

void	debug_obj(t_scene scene,  __global t_obj *objs)
{
	int		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene.objs_number)
	{
		printf("\nname %d\n", objs[i].type);
		printf("color %X\n", objs[i].color);
		//printf("dir %f, %f, %f\n", objs[i].dir.x, objs[i].dir.y, objs[i].dir.z);
		printf("pos %f, %f, %f\n", objs[i].pos.x, objs[i].pos.y, objs[i].pos.z);
		printf("alpha %f\n", objs[i].alpha);
		printf("rayon %f\n\n", objs[i].rayon);
		i++;
	}
}

void	debug_scene(t_scene scene, __global t_obj *objs, __global t_light *lights)
{

	printf("scenenb %i\n", scene.objs_number);
	printf("scenenb %i\n", scene.lights_number);
	
//	printf("campos %f, %f, %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
//	printf("camdir %f, %f, %f\n", scene->cam.dir.x, scene->cam.dir.y, scene->cam.dir.z);
	debug_obj(scene, objs);
	debug_light(scene, lights);
}

__kernel void	calc(__global int *output, __global t_obj *objs, __global t_light *lights, int height, int width, float width_per_height, int objs_number, int lights_number, float3 cam_dir, float3 cam_pos, float3 norm_hor, float3 norm_vert)
{
	float3	ray;
	float	coef;
	t_scene	scene;
	int		pix_vert;
	int		pix_hor;
	int		i =  get_global_id(0);
//	printf("%i\n", i

	scene.objs_number = objs_number;
	scene.lights_number = lights_number;
	scene.cam_dir = cam_dir;
	scene.cam_pos = cam_pos;
	
//	printf("scene objs number %i\n", scene.objs_number);
//	printf("scenen light number %i\n", scene.lights_number);

//	if (i == 1)
//		debug_scene(scene, objs, lights);
	pix_hor = i % width;
	pix_vert = i / width;

	ray.x = cam_dir.x;
	ray.y = cam_dir.y;
	ray.z = cam_dir.z;

	ray = NORMALIZE(ray);
	coef = (((float)pix_vert - ((float)height / 2)) / ((float)height / 2)) * 0.3; //varie entre -0.66 et +0.66
//	printf("coef %f\n", coef);
	ray.z += -coef * norm_vert.z;
	coef = (((float)pix_hor - ((float)width / 2)) / ((float)width / 2)) * 0.3 * width_per_height; //varie entre -0.66 et +0.66
//	printf("coef %f\n", coef);
	ray.y += coef * norm_hor.y;
	ray.x += coef * norm_hor.x;
	ray = NORMALIZE(ray);
//	printf("ray %f, %f, %f\n", ray.x, ray.y, ray.z);
	output[i] = calc_rayon(objs, lights, scene, ray);
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
//	printf("pos %f, %f, %f", pos.x, pos.y, pos.z);
//	printf("rayon %f,", obj->rayon);
//	printf("a %f, b %f, c %f, delta %f ,result %f, ", a, b, c, delta, ((-b - (sqrt(delta))) / (2 * a)));
	if (delta < 0)
		return (0);
//	return (1);
//	printf("sqrt %f", sqrt(delta));
	t = ft_min_positiv(((-b - (sqrt(delta))) / (2 * a)), ((-b + (sqrt(delta))) / (2 * a)));
//	printf("t %f", t);
	if (t <= 0)
	{
	//	printf("t < 0");
		return (0);
	}
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
float	calc_dist(float t, float3 ray)
{
	float3	cam_to_obj;
	float	dist;

	cam_to_obj = mult_vect(ray, t);
	dist = norme_carre(cam_to_obj);
	/*
**		if (dist < 0.1)
**			return (0);
*/
	return (dist);
}

void	assign_intersect_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	output->intersect = mult_vect(ray, output->t);
	output->intersect = add_vect(output->intersect, pos);
	output->norm = output->intersect;
	output->intersect = add_vect(output->intersect, obj.pos);
}

void	assign_norm_vect(t_obj obj, float t, float3 pos, float3 ray, struct s_result_hit *output)
{
	(void)pos;
	(void)ray;
	(void)t;
	if (obj.type == PLAN)
		output->norm = obj.dir;
}

int		hit(__global t_obj *objs, int objs_number, float3 cam_pos, float3 ray,  struct s_result_hit *result_hit)
{
	float	dist;
	float3	pos_translated;
	float	t;
	int	i = 0;
	t_obj	obj;
	int		hit;

	hit = 0;
	result_hit->dist = 1000.0;
//	printf ("scene objsnumber", scene.objs_number);
	while (i < objs_number)
	{
			obj = objs[i];
			pos_translated = sub_vect(cam_pos, obj.pos);
		//	printf("scene.cam_pos %f, %f, %f", scene.cam_pos.x, scene.cam_pos.y, scene.cam_pos.z);
			t = calc_obj(&obj, pos_translated, ray); //TODO objs est ds la stack de la fct
			//printf("t %f", t );
			dist = calc_dist(t, ray);
			if (dist > 0.1 && dist < result_hit->dist)
			{
		//	printf("dist %f", dist);
				hit = 1;
				result_hit->dist = dist;
				result_hit->t = t;
				result_hit->obj = obj;
				assign_intersect_norm_vect(obj, t, pos_translated, ray, result_hit);
				assign_norm_vect(obj, t, pos_translated, ray, result_hit);
			}
		i++;
	}
	if (!hit)
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
	ray = NORMALIZE(ray); //??
	intensite_specular = scalar_product(reflection_vect, ray);
	if (intensite_specular < 0)
		return (0);
	intensite_specular = 0.3 * pow(intensite_specular, 11);
	return (intensite_specular);
}

float	calc_lum_diffuse(struct s_result_hit *result_hit, float3 ray, float3 lum_vect)
{
	float	intensite_diffuse;

	(void)ray;
	result_hit->norm = NORMALIZE(result_hit->norm); /////////////////////////////////////////////////////////////////////////////TODO danger
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	intensite_diffuse = scalar_product(lum_vect, result_hit->norm);
	if (intensite_diffuse > 0)
		return (0);
	return (ft_abs_float(intensite_diffuse));
}

float3	calc_lum_vect(float3 intersect, t_light lum)
{
	float3 lum_vect;
	//	printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	sub_vect(lum_pos, lum.pos, obj->pos);
	lum_vect = sub_vect(intersect, lum.pos);
	lum_vect = NORMALIZE(lum_vect);
	return (lum_vect);
}

int	calc_all_lum(__global t_light *lights, __global t_obj *objs, t_scene scene, struct s_result_hit *result_hit, float3 ray)
{
	float	intensite_diffuse;
	int	color;
	float	intensite_specular;
	float3	lum_vect;
	t_light	light;
	int		i;

	intensite_specular = 0;
	intensite_diffuse = 0.1;

	i = 0;
	while (i < scene.lights_number)
	{
		light = lights[i];
		lum_vect = calc_lum_vect(result_hit->intersect, light);
		/*
		**				if (obj_between_light(scene, obj, tmp, lum_vect))
		**					return (0xFF0000);
		*/
		if (!obj_between_light(scene, objs, light, lum_vect, *result_hit))
		{
			intensite_diffuse += calc_lum_diffuse(result_hit, ray, lum_vect);
			intensite_specular += calc_lum_specular(result_hit, ray, lum_vect);
		}
		i++;
	}
	color = calc_color(intensite_diffuse, result_hit->obj.color);
	color = calc_color_specular(intensite_specular, color);
	return (color);
}
int	obj_between_light(t_scene scene, __global t_obj *objs, t_light lum, float3 lum_vect, struct s_result_hit  hit_forward)
{
	struct s_result_hit hit_backward;
	float3		obj_obj;
	float3		obj_light;

	lum_vect = mult_vect(lum_vect, -1);
	if (!hit(objs, scene.objs_number, hit_forward.intersect, lum_vect, &hit_backward))
		return (0);
	obj_obj = sub_vect(hit_forward.intersect, hit_backward.intersect);
	obj_light = sub_vect(hit_forward.intersect, lum.pos);
//	if (hit_forward.obj == hit_backward.obj)
//		return (0);
	if (norme_carre(obj_obj) < norme_carre(obj_light))
	{
//		printf("ombre\n");
		return (1);
	}
//	printf("\nobj_intersect x %f\ny %f\nz %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
//	printf("\nhit_obj_intersect x %f\ny %f\nz %f\n", hit_obj_intersect.x, hit_obj_intersect.y, hit_obj_intersect.z);
	return (0);
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