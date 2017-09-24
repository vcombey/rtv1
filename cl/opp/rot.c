float3 rot(float3 v, float teta)
{
	float tmp;

	tmp = v.x;
	v.x = v.x * cos(teta) - v.y * sin(teta);
	v.y = tmp * sin(teta) + v.y * cos(teta);
	return (v);
}

static float	mat_mult_coef(float a[3][3], float b[3][3], int a_line, int b_col)
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

void	mat_mult(float res[3][3], float a[3][3], float b[3][3])
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

static float	mat_mult_vect_coef(float a[3][3], float3 b, int a_line)
{
	float	res;

	res = 0;
	res += a[a_line][0] * b.x;
	res += a[a_line][1] * b.y;
	res += a[a_line][2] * b.z;
	return (res);
}

float3	mat_mult_vect(float a[3][3], float3 x)
{
	float3	res;

	res.x = mat_mult_vect_coef(a, x, 0);
	res.y = mat_mult_vect_coef(a, x, 1);
	res.z = mat_mult_vect_coef(a, x, 2);
	return (res);
}

float3	calc_rotation_figure(float3 ray, float3 v)
{
	v = NORMALIZE(v);
	float	mat_x[3][3] = {
		{1, 0, 0},
		{0, v.z, -v.y},
		{0, v.y, v.z},
	};
	float	mat_y[3][3] = {
		{v.z, 0, v.x},
		{0, 1, 0},
		{-v.x, 0, v.z},
	};
	float	mat_z[3][3] = {
		{v.z, -v.x, 0},
		{v.x, v.z, 0},
		{0, 0, 1},
	};
	float	res[3][3];
	mat_mult(res, mat_y, mat_x);
	ray = mat_mult_vect(res, ray);

	ray = NORMALIZE(ray);
	return (ray);
	(void)mat_y;
	(void)mat_z;
}

float3	rodrigues(float3 input, float3 v, float teta)
{
	float3	res;
	float	mat[3][3] = {
		{cos(teta) + (1 - cos(teta)) * v.x * v.x,			(1 - cos(teta)) * v.x * v.y - sin(teta) * v.z,				(1 - cos(teta)) * v.x * v.z + sin(teta) * v.y},
		{(1 - cos(teta)) * v.x * v.y - sin(teta) * v.z,		cos(teta) + (1 - cos(teta)) * v.y * v.y,					(1 - cos(teta)) * v.y * v.z - sin(teta) * v.x},
		{(1 - cos(teta)) * v.x * v.z - sin(teta) * v.y,		(1 - cos(teta)) * v.y * v.z - sin(teta) * v.x,				cos(teta) + (1 - cos(teta)) * v.z * v.z,}
	};

	res = mat_mult_vect(mat, input);

	return (res);
}
