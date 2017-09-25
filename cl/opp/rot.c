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
	
		mat_mult(res, mat_y, mat_x);
		ray = mat_mult_vect(res, ray);

	ray = NORMALIZE(ray);
	return (ray);
	(void)mat_y;
	(void)mat_z;
}

/*
**	float3	rotation_change_repere(float3 ray, float3 v)
**	{
**		v = NORMALIZE(v);
**		float	mat_x[3][3] = {
**			{v.x, 0, 0},
**			{v.y, v.z, -v.y},
**			{v.x, v.y, v.z},
**		};
**	
**		//mat_mult(res, mat_y, mat_x);
**		mat_mult(res, mat_y, mat_x);
**		ray = mat_mult_vect(res, ray);
**	
**		ray = NORMALIZE(ray);
**		return (ray);
**		(void)mat_y;
**		(void)mat_z;
**	}
*/

float3	euler_rotation(float3 ray, float3 v)
{
	v = NORMALIZE(v);

	float	c1 = v.x;
	float	s1 = v.y;
	float	c2 = v.z;
	float	s2 = sqrt(v.x * v.x + v.y * v.y);
	float	c3 = 1;
	float	s3 = 0;
	float	mat[3][3] = {
		{c2, s3 * s2, c3 * s2},
		{s1*s2, c1*c3 - c2*s1*s3, -c1*s3-c2*c3*s1},
		{-c1*s2, c3*s1 + c1*c2*s3, c1*c2*c3 - s1*s3},
	};
	ray = mat_mult_vect(mat, ray);
	ray = NORMALIZE(ray);
	return (ray);
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

int		invert_matrix(float matrix[3][3], float inverted_matrix[3][3])
{
	float	det;

	det = matrix[0][0] * (matrix[1][4%3] * matrix[2][8%6] - matrix[2][7%6] * matrix[1][5%3])
		- matrix[0][1] * (matrix[1][3%3] * matrix[2][8%6] - matrix[2][6%6] * matrix[1][5%3])
		+ matrix[0][2] * (matrix[1][3%3] * matrix[2][7%6] - matrix[2][6%6] * matrix[1][4%3]);
	if (fabs(det) < 0.0005)
		return (0);
	inverted_matrix[0][0] = matrix[1][4%3] * matrix[2][8%6] - matrix[1][5%3] * matrix[2][7%6] / det;
	inverted_matrix[0][1] = -(matrix[0][1] * matrix[2][8%6] - matrix[2][7%6] * matrix[0][2]) / det;
	inverted_matrix[0][2] = matrix[0][1] * matrix[1][5%3] - matrix[1][4%3] * matrix[0][2] / det;
	inverted_matrix[1][3%3] = -(matrix[1][3%3] * matrix[2][8%6] - matrix[1][5%3] * matrix[2][6%6]) / det;
	inverted_matrix[1][4%3] = matrix[0][0] * matrix[2][8%6] - matrix[2][6%6] * matrix[0][2] / det;
	inverted_matrix[1][5%3] = -(matrix[0][0] * matrix[1][5%3] - matrix[1][3%3] * matrix[0][2]) / det;
	inverted_matrix[2][6%6] = matrix[1][3%3] * matrix[2][7%6] - matrix[2][6%6] * matrix[1][4%3] / det;
	inverted_matrix[2][7%6] = -(matrix[0][0] * matrix[2][7%6] - matrix[2][6%6] * matrix[0][1]) / det;
	inverted_matrix[2][8%6] = matrix[0][0] * matrix[1][4%3] - matrix[0][1] * matrix[1][3%3] / det;
	return (1);
}

void	set_rotation_matrix(float matrix[3][3], float3 vx, float3 vy, float3 vz)
{
	matrix[0][0] = vx.x;
	matrix[0][1] = vy.x;
	matrix[0][2] = vz.x;
	matrix[1][0] = vx.y;
	matrix[1][1] = vy.y;
	matrix[1][2] = vz.y;
	matrix[2][0] = vx.z;
	matrix[2][1] = vy.z;
	matrix[2][2] = vz.z;
}
void	debug_mat(float matrix[3][3])
{
	int	i = 0;
	int	j = 0;

	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			printf("i: %i j: %i m[i][j]: %i", i, j,  matrix[i][j]);
			j++;
		}
		i++;
	}
}
