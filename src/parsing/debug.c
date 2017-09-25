#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "rt.h"

void	debug_light(t_scene *scene)
{
	int			i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene->lights_number)
	{
		printf("pos %f, %f, %f\n", scene->lights[i].pos.x, scene->lights[i].pos.y, scene->lights[i].pos.z);
		i++;
	}
}

void	debug_obj(t_scene *scene)
{
	int		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene->objs_number)
	{
		printf("\nname %d\n", scene->objs[i].type);
		printf("color %zX\n", scene->objs[i].color);
		printf("dir %f, %f, %f\n", scene->objs[i].dirz.x, scene->objs[i].dirz.y, scene->objs[i].dirz.z);
		printf("pos %f, %f, %f\n", scene->objs[i].pos.x, scene->objs[i].pos.y, scene->objs[i].pos.z);
		printf("alpha %f\n", scene->objs[i].alpha);
		printf("rayon %f\n\n", scene->objs[i].rayon);
		i++;
	}
}

void	debug_scene(t_scene *scene)
{
	printf("name %s\n", scene->name);
	printf("width %zu\n", scene->width);
	printf("height %zu\n", scene->height);
	printf("rot %f, %f, %f\n", scene->rot.x, scene->rot.y, scene->rot.z);
	printf("campos %f, %f, %f\n", scene->cam.pos.x, scene->cam.pos.y, scene->cam.pos.z);
	printf("camdir %f, %f, %f\n", scene->cam.dir.x, scene->cam.dir.y, scene->cam.dir.z);
	debug_obj(scene);
	debug_light(scene);
}

void	debug(t_yaml *lines, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		printf("tab: %zu, key: %s, value: %s\n", lines[i].tab, lines[i].key, lines[i].value);
		i++;
	}
}
