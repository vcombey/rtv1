#include "rt.h"
#include <stdlib.h>

int		ft_key_pressed(int keycode, void *env)
{
	t_env	*cast;

	cast = (t_env *)env;
	if (keycode == KEY_UP)
		cast->up = 1;
	if (keycode == KEY_DOWN)
		cast->down = 1;
	if (keycode == KEY_RIGHT)
		cast->right = 1;
	if (keycode == KEY_LEFT)
		cast->left = 1;
	if (keycode == KEY_ESCAPE)
		exit(0);
	return (0);
}

int		ft_key_release(int keycode, void *env)
{
	t_env	*cast;

	cast = (t_env *)env;
	if (keycode == KEY_UP)
		cast->up = 0;
	if (keycode == KEY_DOWN)
		cast->down = 0;
	if (keycode == KEY_RIGHT)
		cast->right = 0;
	if (keycode == KEY_LEFT)
		cast->left = 0;
	return (0);
}
