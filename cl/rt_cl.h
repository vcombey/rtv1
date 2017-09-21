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
