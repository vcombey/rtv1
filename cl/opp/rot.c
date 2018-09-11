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

float3	mat_mult_vect(float a[3][3], float3 v)
{
	float3	res;

	res.x = a[0][0] * v.x + a[0][1] * v.y + a[0][2] * v.z;
	res.y = a[1][0] * v.x + a[1][1] * v.y + a[1][2] * v.z;
	res.z = a[2][0] * v.x + a[2][1] * v.y + a[2][2] * v.z;
	return (res);
}

float3	calc_rotation_figure(float3 ray, float3 v)
{
	v = normalize(v);
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

	ray = normalize(ray);
	return (ray);
	(void)mat_y;
	(void)mat_z;
}

/*
**	float3	rotation_change_repere(float3 ray, float3 v)
**	{
**		v = normalize(v);
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
**		ray = normalize(ray);
**		return (ray);
**		(void)mat_y;
**		(void)mat_z;
**	}
*/

float3	euler_rotation(float3 ray, float3 v)
{
	v = normalize(v);

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
	ray = normalize(ray);
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

int		invert_matrix(float m[3][3], float inv_m[3][3])
{
	float	det;

	det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
		- m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2])
		+ m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
	if (fabsf(det) < 0.0005)
		return (0);
	inv_m[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1] / det;
	inv_m[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) / det;
	inv_m[0][2] = m[0][1] * m[1][2] - m[1][1] * m[0][2] / det;
	inv_m[1][0] = -(m[1][0] * m[2][2] - m[1][2] * m[2][0]) / det;
	inv_m[1][1] = m[0][0] * m[2][2] - m[2][0] * m[0][2] / det;
	inv_m[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) / det;
	inv_m[2][0] = m[1][0] * m[2][1] - m[2][0] * m[1][1] / det;
	inv_m[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) / det;
	inv_m[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0] / det;
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
