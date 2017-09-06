#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static	t_func	g_scene_func[] =
{
	{"sphere", &get_sphere},
	{"plan", &get_plan},
	{"cone", &get_cone},
	{"cylindre", &get_cylindre},
	{NULL, NULL},
};

size_t	get_sphere(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	(void)len;
	printf("sphere\n");
	new = ft_new_obj();
	new->name = ft_strdup("sphere");
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		printf("\tpropriety: %s\n", lines[i].key);
		if (ft_strequ(lines[i].key, "origin"))
			get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "rotatexyz"))
			get_coordinates(new->rot, lines[i].value);
		else if (ft_strequ(lines[i].key, "rayon"))
			new->rayon = get_rayon(lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	ft_obj_add(new, &scene->objs);
	return (i);
}

size_t	get_plan(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	(void)len;
	printf("plan\n");
	new = ft_new_obj();
	new->name = ft_strdup("plan");
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		printf("\tpropriety: %s\n", lines[i].key);
		if (ft_strequ(lines[i].key, "origin"))
			get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "rotatexyz"))
			get_coordinates(new->rot, lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	ft_obj_add(new, &scene->objs);
	return (i);
}

size_t	get_cylindre(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	(void)len;
	printf("cylindre\n");
	new = ft_new_obj();
	new->name = ft_strdup("cylindre");
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		printf("\tpropriety: %s\n", lines[i].key);
		if (ft_strequ(lines[i].key, "origin"))
			get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "rotatexyz"))
			get_coordinates(new->rot, lines[i].value);
		else if (ft_strequ(lines[i].key, "rayon"))
			new->rayon = get_rayon(lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	ft_obj_add(new, &scene->objs);
	return (i);
}

size_t	get_cone(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_obj	*new;

	(void)len;
	printf("cone\n");
	new = ft_new_obj();
	new->name = ft_strdup("cone");
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		printf("\tpropriety: %s\n", lines[i].key);
		if (ft_strequ(lines[i].key, "origin"))
			get_coordinates(new->pos, lines[i].value);
		else if (ft_strequ(lines[i].key, "rotatexyz"))
			get_coordinates(new->rot, lines[i].value);
		else if (ft_strequ(lines[i].key, "alpha"))
			new->alpha = get_rayon(lines[i].value);
		else if (ft_strequ(lines[i].key, "colorRGB"))
			new->color = get_hexa(lines[i].value);
		else
			fatal("invalid object propriety");
		i++;
	}
	ft_obj_add(new, &scene->objs);
	return (i);
}

size_t	get_all_objects(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t		k;
	size_t	tab;

	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("invalid objects value");
	scene->objs = NULL;
	i++;
	while (i < len && lines[i].tab == tab + 1)
	{
		k = 0;
		while (g_scene_func[k].key && !ft_strequ(g_scene_func[k].key, lines[i].key))
			k++;
		if (g_scene_func[k].f == NULL)
			fatal("invalid object name");
		if (lines[i].value[0])
			fatal("object has bad value");
		i = g_scene_func[k].f(lines, i, scene, len);
	}
	return (i);
}
