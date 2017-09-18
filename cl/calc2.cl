__kernel void	calc(
__global int *output,
size_t height,
size_t width,
size_t startx,
size_t starty,
size_t size)
{
	size_t	pix_vert;
	size_t	pix_hor;

	int		i =  get_global_id(0);
	pix_hor = i % width;
	pix_vert = i / width;
	if (pix_hor > startx && pix_hor < startx + size && pix_vert > starty && pix_vert < starty + size)
		output[i] = 255;
	else
		output[i] = 0;
}