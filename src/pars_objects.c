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

size_t	get_all_objects(t_yaml *lines, size_t i, t_scene *scene)
{
	if (lines[i].value[0])
		fatal("invalid objects value");
	scene->name = ft_strdup(lines[i].value);
	return (i + 1);
}
