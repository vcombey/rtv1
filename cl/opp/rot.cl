static float	mat_mult_coef(float3 a[3], float3 b[3], int a_line, int b_col)
{
	int	i;
	float	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i][b_col];
		i++;
	}
	return (res);
}

void	mat_mult(float3 res[3], float3 a[3], float3 b[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i][j] = mat_mult_coef(a, b, i, j);
			j++;
		}
		i++;
	}
}

static float	mat_mult_vect_coef(float3 a[3], float3 b, int a_line)
{
	int	i;
	float	res;

	res = 0;
	i = 0;
	while (i < 3)
	{
		res += a[a_line][i] * b[i];
		i++;
	}
	return (res);
}

void	mat_mult_vect(float3 res, float3 a[3], float3 x)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		res[i] = mat_mult_vect_coef(a, x, i);
		i++;
	}
}

void	calc_rotation_figure(float3 ray, float3 v)
{
//	NORMALIZE(v);
	float	mat_x[3][3] = {
		{1, 0, 0},
		{0, v.z, -v.y},
		{0, v.y, v.z},
	};
	float	mat_y[3][3] = {
		{v.z, 0, -v.x},
		{0, 1, 0},
		{v.x, 0, v.z},
	};
	float	mat_z[3][3] = {
		{v.z, -v.x, 0},
		{v.x, v.z, 0},
		{0, 0, 1},
	};
	float	res[3][3];
	mat_mult(res, mat_y, mat_x);
	mat_mult_vect(ray, res, ray);
	(void)mat_y;
	(void)mat_z;
}
