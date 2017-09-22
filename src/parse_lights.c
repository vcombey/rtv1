#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

size_t	get_light(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_light	*new_light;

	(void)len;
	new_light = &scene->lights[scene->lights_number];
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("bad light");
	i++;
	printf("origin\n");
	if (ft_strequ(lines[i].key, "origin"))
		new_light->pos = get_coordinates(new_light->pos, lines[i].value);
	else
		fatal("bad light propriety");
	i++;
	scene->lights_number++;
	return (i);
}
