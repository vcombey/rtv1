static void		ft_pixelput(__global char *output, int x, int y, int color, size_t height, size_t width)
{
	int				i;
	int				dest;
	unsigned int	new_color;

	if (y < 0 || x < 0)
		return ;
	dest = y * 100 + x * (32 / 8);
	if ((int)(height * width * (32 / 8)) <= dest)
		return ;
	if (dest < 0)
		return ;
	i = -1;
	while (++i < 32 / 8)
	{
		output[dest + i] = new_color >> (i * 8) & 0xFF;
	}
}


__kernel void	calc(
__global char *output,
size_t height,
size_t width)
{
	int		i =  get_global_id(0);
	output[i] = i % 255;
}
