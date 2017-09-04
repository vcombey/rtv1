#ifndef RT_H
# define RT_H

#include <string.h>

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
	char			*ptr;
	int				bpp;
	int				size_line;
	int				endian;
}					t_env;

typedef struct		s_obj
{
	double			pos[3];
	double			rot[3];
	double			alpha;
	char			*name;
	struct s_obj	*next;
}					t_obj;

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
}					t_scene;

typedef struct	s_func
{
	char		*key;
	size_t		(*f)(t_yaml *, size_t, t_scene *k, size_t);
}				t_func;

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 800
# define WIDTH_PER_HEIGHT SCREEN_WIDTH/SCREEN_HEIGHT

t_env				*env(void);
int					init_env(t_env *env);
void	calc(t_env *env);

void				ft_pixelput(t_env *env, int x, int y, int color);

double	calc_delta(double a, double b, double c);
double	ft_min(double u, double v);
double	ft_abs_double(double u);
void	mult_vect(double res[3], double v[3], double t);
void	div_vect(double res[3], double v[3], double t);
void	add_vect(double res[3], double u[3], double v[3]);
void	sub_vect(double res[3], double u[3], double v[3]);
double	norme_carre(double v[3]);
double	scalar_product(double u[3], double v[3]);
void	normalize(double v[3]);
void	parse_file(char *filename, t_scene *scene);
void	get_coordinates(double	*res[3], char *value);
void	parse_scene(t_yaml *lines, size_t len, t_scene *scene);
size_t	get_name(t_yaml *lines, size_t i, t_scene *scene);
size_t	get_windows_size(t_yaml *lines, size_t i, t_scene *scene);
size_t	get_camera(t_yaml *lines, size_t i, t_scene *scene);
size_t	get_all_objects(t_yaml *lines, size_t i, t_scene *scene);

#endif
