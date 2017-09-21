float3	mult_vect( float3 v, double t)
{
	float3	res;

	res.x = v.x * t;
	res.y = v.y * t;
	res.z = v.z * t;
	return (res);
}

float3	div_vect(float3 v, double t)
{
	float3	res;

	if (t == 0)
		return ;
	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

float3	add_vect(float3 u, float3 v)
{
	float3	res;

	res.x = u.x + v.x;
	res.y = u.y + v.y;
	res.z = u.z + v.z;
	return (res);
}

float3	cpy_vect(float3 u, float3 v)
{
	float3	res;

	u.x = v.x;
	u.y = v.y;
	u.z = v.z;
	return (res);
}

float3	sub_vect(float3 u, float3 v)
{
	float3	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	res.z = u.z - v.z;
	return (res);
}

float3	vectorial_product(float3 u, float3 v)
{
	float3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}
