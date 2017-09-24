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
	int				indice;
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
	float3			ray;
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
float	ft_min_positiv(float a, float b);
float	calc_plan(t_obj *obj, float3 pos, float3 ray);
float	calc_cone(t_obj *obj, float3 pos, float3 ray);
float	calc_cylindre(t_obj *obj, float3 pos, float3 ray);
float	calc_sphere(t_obj *obj, float3 pos, float3 ray);
float	calc_obj(t_obj *obj, float3 pos, float3 ray);
float	calc_dist(float t, float3 ray, t_obj *obj);
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
float3	sub_vect(float3 u, float3 v);
float3	vectorial_product(float3 u, float3 v);
float3 rot(float3 v, float teta);
void	mat_mult(float res[3][3], float a[3][3], float b[3][3]);
float3	mat_mult_vect(float a[3][3], float3 x);
float3	calc_rotation_figure(float3 ray, float3 v);
float3	rodrigues(float3 input, float3 v, float teta);
#endif
