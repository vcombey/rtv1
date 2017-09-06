#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

t_light	*ft_new_light(void)
{
	t_light	*new;
	new = ft_memalloc(sizeof(t_light));
	new->pos = ft_memalloc(sizeof(double) * 3);
	return (new);
}

void	ft_light_add(t_light *new_node, t_light **first)
{
	new_node->next = *first;
	*first = new_node;
}

size_t	get_light(t_yaml *lines, size_t i, t_scene *scene, size_t len)
{
	size_t	tab;
	t_light	*new_light;

	(void)len;
	new_light = ft_new_light();
	tab = lines[i].tab;
	if (lines[i].value[0])
		fatal("bad light");
	i++;
	printf("origin\n");
	if (ft_strequ(lines[i].key, "origin"))
		get_coordinates(new_light->pos, lines[i].value);
	else
		fatal("bad light propriety");
	ft_light_add(new_light, &scene->lights);
	i++;
	return (i);
}
