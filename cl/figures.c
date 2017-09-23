float	ft_min_positiv(float a, float b)
{
	if (a < 0 && b > 0)
		return (b);
	if (a > 0 && b < 0)
		return (a);
	return (ft_min(a, b));
}

float	calc_plan(t_obj *obj, float3 pos, float3 ray)
{
	float	t;
	float	diviseur;
	/*
**		float	obj->dir[3];
**	
**		obj->dir.x = 1;
**		obj->dir.y = 1;
**		obj->dir.z = 1;
*/
	diviseur = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
	if (ft_abs_float(diviseur) < 0.01)
		return (0);
	t = pos.x * obj->dir.x + pos.y * obj->dir.y + pos.z * obj->dir.z;
	t = -t / diviseur;

	if (t < 0.001)
		return (0);

	return (t);
}

float	calc_cone(t_obj *obj, float3 pos, float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;
	float	alpha = 0.7;
	float	tan_alpha_carre = tan(alpha) * tan(alpha);

//	calc_rotation_figure(ray, obj->dir);
	a = ray.x * ray.x + ray.y * ray.y - ray.z * ray.z * tan_alpha_carre;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * pos.z * ray.z * tan_alpha_carre;
	c = pos.x * pos.x + pos.y * pos.y - pos.z * pos.z * tan_alpha_carre;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	return (t);
}

/*
**	float	calc_cylindre_quifait_cone(t_obj *obj, float3 pos, float3 ray)
**	{
**		float	delta;
**		float	a;
**		float	b;
**		float	c;
**		float	t;
**		float	coef_1;
**		float	coef_2;
**		float	coef_div;
**	
**	//	calc_rotation_figure(ray, obj->dir);
**	
**		coef_div = obj->dir.x * obj->dir.x + obj->dir.y * obj->dir.y + obj->dir.z * obj->dir.z;
**		if (coef_div == 0)
**			return (0);
**		coef_1 = obj->dir.x * ray.x + obj->dir.y * ray.y + obj->dir.z * ray.z;
**		coef_2 = obj->dir.x * pos.x + obj->dir.y * pos.y + obj->dir.z * pos.z;
**		a = ray.x * ray.x + ray.y * ray.y - coef_1 * coef_1 / coef_div;
**		b = 2 * pos.x * ray.x + 2 * pos.y * ray.y - 2 * coef_1 * coef_2 / coef_div;
**		c = pos.x * pos.x + pos.y * pos.y - obj->rayon * obj->rayon - coef_2 * coef_2 / coef_div;
**		delta = calc_delta(a, b, c);
**		//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
**		if (delta < 0)
**			return (0x0);
**		t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
**		if (t < 0.1)
**			return (0);
**		return (t);
**	}
*/

float	calc_cylindre(t_obj *obj, float3 pos, float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;
	float	coef_1;
	float	coef_2;
	float	coef_div;

//	calc_rotation_figure(ray, obj->dir);

	a = ray.x * ray.x + ray.y * ray.y;
	b = 2 * pos.x * ray.x + 2 * pos.y * ray.y;
	c = pos.x * pos.x + pos.y * pos.y - obj->rayon * obj->rayon;
	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0x0);
	t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	if (t < 0.001)
		return (0);
	return (t);
}

float	calc_sphere(t_obj *obj, float3 pos, float3 ray)
{
	float	delta;
	float	a;
	float	b;
	float	c;
	float	t;

	a = norme_carre(ray);
	b = 2 * scalar_product(ray, pos);
	c = norme_carre(pos) - obj->rayon * obj->rayon;

	delta = calc_delta(a, b, c);
//	printf("pos %f, %f, %f", pos.x, pos.y, pos.z);
//	printf("rayon %f,", obj->rayon);
//	printf("a %f, b %f, c %f, delta %f ,result %f, ", a, b, c, delta, ((-b - (sqrt(delta))) / (2 * a)));
	if (delta < 0)
		return (0);
//	return (1);
//	printf("sqrt %f", sqrt(delta));
	t = ft_min_positiv(((-b - (sqrt(delta))) / (2 * a)), ((-b + (sqrt(delta))) / (2 * a)));
//	printf("t %f", t);
	if (t <= 0)
	{
	//	printf("t < 0");
		return (0);
	}
	return (t);
}

float	calc_obj(t_obj *obj, float3 pos, float3 ray)
{

	if (obj->type == SPHERE)
		return (calc_sphere(obj, pos, ray));
	if (obj->type == PLAN)
		return (calc_plan(obj, pos, ray));
	if (obj->type == CONE)
		return (calc_cone(obj, pos, ray));
	if (obj->type == CYLINDRE)
		return (calc_cylindre(obj, pos, ray));
	return (0);
}
