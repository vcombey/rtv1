#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static	t_func	g_scene_func[] =
{
	{"name", &get_name},
	{"camera", &get_camera},
	{"windows_size", &get_windows_size},
	{"object", &get_all_objects},
	{NULL, NULL},
};

size_t	get_name(t_yaml *lines, size_t i, t_scene *scene)
{
	if (!lines[i].value[0])
		fatal("parse error");
	scene->name = ft_strdup(lines[i].value);
	return (i + 1);
}

size_t	get_windows_size(t_yaml *lines, size_t i, t_scene *scene)
{
	char	*coord;

	if (!lines[i].value[0])
		fatal("parse error");
	coord = lines[i].value;
	scene->width = strtod(coord, &coord);
	scene->height = strtod(coord, &coord);
	return (i + 1);
}

size_t	get_camera(t_yaml *lines, size_t i, t_scene *scene)
{
	size_t	tab;

	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("parse error");
	i++;
	while (lines[i].tab == tab + 1)
	{
		if (ft_strequ(lines[i].key, "origin"))
			get_coordinates((double **)&scene->cam.pos, lines[i].value);
		if (ft_strequ(lines[i].key, "rotatexyz"))
			get_coordinates((double **)&scene->cam.pos, lines[i].value);
	}
	return (i + 1);
}

void	parse_scene(t_yaml *lines, size_t len, t_scene *scene)
{
	size_t		i;
	size_t		k;

	if (len == 0 || len == 1)
		fatal("parse error");
	i = 0;
	if (!ft_strequ(lines[0].key, "scene"))
		fatal("parse error");
	i++;
	while (i < len)
	{
		printf("tab: %zu, key: %s, value: %s\n", lines[i].tab, lines[i].key, lines[i].value);
		k = 0;
		while (g_scene_func[k].key && !ft_strequ(g_scene_func[i].key, lines[i].key))
			k++;
		if (g_scene_func[k].f == NULL)
			fatal("parse error");
		g_scene_func[k].f(lines + i, i, scene, len);
	}
}
