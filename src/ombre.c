
size_t	calc_sphere(t_obj *obj, t_cam cam, double ray[3])
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	t;
	size_t	dist;

	ft_memset(obj->intersect, 0, sizeof(double) * 3);
	a = norme_carre(ray);
	b = 2 * scalar_product(ray, cam.pos);
	c = norme_carre(cam.pos) - obj->rayon * obj->rayon;

	delta = calc_delta(a, b, c);
	//printf("a %f, b %f, c %f, delta %f\n", a, b, c, delta);
	if (delta < 0)
		return (0);
	t = ft_min_positiv((-b - sqrt(delta)) / (2 * a), (-b + sqrt(delta)) / (2 * a));
	if (t < 0)
		return (0);
	mult_vect(obj->intersect, ray, t);
	dist = norme_carre(obj->intersect);
	if (dist < 0.1)
		return (0);
	add_vect(obj->intersect, obj->intersect, cam.pos);
	cpy_vect(obj->norm, obj->intersect); // cpy dans obj norm
	add_vect(obj->intersect, obj->intersect, obj->pos);
	return (dist);
}
