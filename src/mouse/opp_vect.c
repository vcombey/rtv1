#include "rt.h"
cl_float3	mult_vect( cl_float3 v, float t)
{
	cl_float3	res;

	res.x = v.x * t;
	res.y = v.y * t;
	res.z = v.z * t;
	return (res);
}

cl_float3	div_vect(cl_float3 v, float t)
{
	cl_float3	res;

	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
	return (res);
}

cl_float3	add_vect(cl_float3 u, cl_float3 v)
{
	cl_float3	res;

	res.x = u.x + v.x;
	res.y = u.y + v.y;
	res.z = u.z + v.z;
	return (res);
}

cl_float3	sub_vect(cl_float3 u, cl_float3 v)
{
	cl_float3	res;

	res.x = u.x - v.x;
	res.y = u.y - v.y;
	res.z = u.z - v.z;
	return (res);
}

cl_float3	vectorial_product(cl_float3 u, cl_float3 v)
{
	cl_float3	res;

	res.x = u.y * v.z - u.z * v.y;
	res.y = u.z * v.x - u.x * v.z;
	res.z = u.x * v.y - u.y * v.x;
	return (res);
}
