typedef struct		s_obj
{
	int				type;
	float3		pos;
	float3		dir;
	size_t			color;
	double			alpha;
	double			rayon;
}					t_obj;

__kernel void	calc(
__global int *output,
 __global t_obj *objs
)
{

	printf("obj o %i ", objs[0].type);
int	i	 = get_global_id(0);
	printf("%i\n", i);
	output[i] = 0xff00ff;
}
