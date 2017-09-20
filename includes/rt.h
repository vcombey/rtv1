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
	cl_float3			dir;
	cl_float3			pos;
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
	cl_float3		pos;
	cl_float3		dir;
	size_t			color;
	double			alpha;
	double			rayon;
	cl_float3			intersect;
	cl_float3			norm;
}					t_obj;

typedef struct		s_light
{
	cl_float3			pos;
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
	cl_float3		rot;
	size_t			width;
	size_t			height;
	t_cam			cam;
	t_obj			*objs;
	size_t			objs_number;
	t_light			*lights;
	size_t			lights_number;
}					t_scene;

typedef struct	s_func
{
	char		*key;
	size_t		(*f)(t_yaml *, size_t, t_scene *k, size_t);
}				t_func;

# define SPHERE 0
# define CONE 1
# define PLAN 2
# define CYLINDRE 3

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

void	parse_file(char *filename, t_scene *scene);
cl_float3	get_coordinates(cl_float3	res, char *value);
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

int		ft_key_pressed(int keycode, void *env);
int		ft_key_release(int keycode, void *env);
t_env	*singleton_env();
int			recalc_img(void *scene);

void	init_scene(t_scene *scene);
int		quit(void *param);

const char *getErrorString(cl_int error);
void	mv_up(t_env *env, t_cam *cam);
void	mv_down(t_env *env, t_cam *cam);
void	rot_right(t_env *env, t_cam *cam);
void	rot_left(t_env *env, t_cam *cam);

#endif
