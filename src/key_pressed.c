#include "rt.h"
#include <stdlib.h>
#include <stdio.h>

int		ft_key_pressed(int keycode, void *env)
{
	t_env	*cast;

	printf("\n%d\n", keycode);
	cast = (t_env *)env;
	if (keycode == 13)
		cast->rot_right = 1;
	if (keycode == KEY_UP)
		cast->up = 1;
	if (keycode == KEY_DOWN)
		cast->down = 1;
	if (keycode == KEY_RIGHT)
		cast->right = 1;
	if (keycode == KEY_LEFT)
		cast->left = 1;
	if (keycode == KEY_SHIFT_LEFT)
		cast->key_shift_left = 1;
	if (keycode == KEY_SHIFT_RIGHT)
		cast->key_shift_right = 1;
	if (keycode == KEY_R)
		cast->key_r = 1;
	if (keycode == KEY_T)
		cast->key_t = 1;
	if (keycode == KEY_ESCAPE)
		exit(0);
	return (0);
}

int		ft_key_release(int keycode, void *env)
{
	t_env	*cast;

	cast = (t_env *)env;
	if (keycode == 14)
		cast->rot_left = 1;
	if (keycode == KEY_UP)
		cast->up = 0;
	if (keycode == KEY_DOWN)
		cast->down = 0;
	if (keycode == KEY_RIGHT)
		cast->right = 0;
	if (keycode == KEY_LEFT)
		cast->left = 0;
	if (keycode == KEY_SHIFT_LEFT)
		cast->key_shift_left = 0;
	if (keycode == KEY_SHIFT_RIGHT)
		cast->key_shift_right = 0;
	if (keycode == KEY_R)
		cast->key_r = 0;
	if (keycode == KEY_T)
		cast->key_t = 0;
	return (0);
}
