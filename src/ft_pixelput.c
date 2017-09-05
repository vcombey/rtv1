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
