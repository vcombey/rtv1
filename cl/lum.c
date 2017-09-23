int	calc_color(float coef_lum, int color)
{
	int	r;
	int	g;
	int	b;

	r = (int)(coef_lum * (color >> 16));
	if (r > 255)
		r = 255;
	r <<= 16;
	g = (int)(coef_lum * ((color & 0xFF00) >> 8));
	if (g > 255)
		g = 255;
	g <<= 8;
	b = coef_lum * (color & 0xFF);
	if (b > 255)
		b = 255;
	return (r + g + b);
}

int	calc_color_specular(float coef_lum, int color)
{
	int	r;
	int	g;
	int	b;

	coef_lum = coef_lum * 255;
	r = (int)(coef_lum + (color >> 16));
	if (r > 255)
		r = 255;
	r <<= 16;
	g = (int)(coef_lum + ((color & 0xFF00) >> 8));
	if (g > 255)
		g = 255;
	g <<= 8;
	b = coef_lum + (color & 0xFF);
	if (b > 255)
		b = 255;
	return (r + g + b);
}

float	calc_lum_specular(struct s_result_hit *result_hit, float3 ray, float3 lum_vect)
{
	//	float	lum_pos[3];
	float	intensite_specular;
	float3	reflection_vect;

	reflection_vect = mult_vect(result_hit->norm, 2 * scalar_product(lum_vect, result_hit->norm));
	reflection_vect = sub_vect(reflection_vect, lum_vect);
	ray = NORMALIZE(ray); //??
	intensite_specular = scalar_product(reflection_vect, ray);
	if (intensite_specular < 0)
		return (0);
	intensite_specular = 0.3 * pow(intensite_specular, 11);
	return (intensite_specular);
}

float	calc_lum_diffuse(struct s_result_hit *result_hit, float3 ray, float3 lum_vect)
{
	float	intensite_diffuse;

	(void)ray;
	result_hit->norm = NORMALIZE(result_hit->norm); /////////////////////////////////////////////////////////////////////////////TODO danger
	//printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	obj->intersectalize(obj->intersect); // pk obj->intersect-sphere n est pas de obj->intersecte rayon ?
	intensite_diffuse = scalar_product(lum_vect, result_hit->norm);
	if (intensite_diffuse > 0)
		return (0);
	return (ft_abs_float(intensite_diffuse));
}

float3	calc_lum_vect(float3 intersect, t_light lum)
{
	float3 lum_vect;
	//	printf("\nobj->intersect x %f, y %f, z %f\n", obj->intersect.x, obj->intersect.y, obj->intersect.z);
	//	sub_vect(lum_pos, lum.pos, obj->pos);
	lum_vect = sub_vect(intersect, lum.pos);
	lum_vect = NORMALIZE(lum_vect);
	return (lum_vect);
}

int	calc_all_lum(__global t_light *lights, t_scene scene, struct s_result_hit *result_hit, float3 ray)
{
	float	intensite_diffuse;
	int	color;
	float	intensite_specular;
	float3	lum_vect;
	t_light	light;
	int		i;

	intensite_specular = 0;
	intensite_diffuse = 0.1;

	i = 0;
	while (i < scene.lights_number)
	{
		light = lights[i];
		lum_vect = calc_lum_vect(result_hit->intersect, light);
		/*
		**				if (obj_between_light(scene, obj, tmp, lum_vect))
		**					return (0xFF0000);
		*/
	//	if (!obj_between_light(scene, obj, light, lum_vect))
	//	{
			intensite_diffuse += calc_lum_diffuse(result_hit, ray, lum_vect);
			intensite_specular += calc_lum_specular(result_hit, ray, lum_vect);
	//	}
		i++;
	}
	color = calc_color(intensite_diffuse, result_hit->obj->color);
	color = calc_color_specular(intensite_specular, color);
	return (color);
}
