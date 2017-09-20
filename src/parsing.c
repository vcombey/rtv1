#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

void	parse_line(char *line, t_yaml *new)
{
	size_t	tab;
	char	*sep;
	char	*comment;

	tab = 0;
	while (*line && *line == '\t')
	{
		tab++;
		line++;
	}
	new->tab = tab;
	if ((comment = ft_strchr(line, '#')))
		*comment = '\0';
	if (!(sep = ft_strchr(line, ':')))
		fatal("bad yaml");
	if (ft_strchr(sep + 1, ':'))
		fatal("bad yaml");
	*sep = '\0';
	new->key = ft_strtrim(line);
//	printf("new->key: %s\n", new->key);
	new->value = ft_strtrim(sep + 1);
//	printf("new->value: %s\n", new->key);
}

void	valid_yaml(t_yaml *lines, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len && i + 1 < len)
	{
//		printf("lines value%s\n", lines[i].value);
		if (lines[i].value[0] && (lines[i].tab < lines[i + 1].tab))
			fatal("bad yaml");
		if (!lines[i].value[0] && lines[i].tab + 1 != lines[i + 1].tab)
			fatal("bad yaml");
		i++;
	}
}

void	debug_light(t_scene *scene)
{
	size_t		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene->lights_number)
	{
		printf("pos %f, %f, %f\n", scene->lights[i].pos.x, scene->lights[i].pos.y, scene->lights[i].pos.z);
	}
}

void	debug_obj(t_scene *scene)
{
	size_t		i;

	i = 0;
//	printf("tmp %zu\n", (size_t)tmp);
	while (i < scene->objs_number)
	{
		printf("name %d\n", scene->objs[i].type);
		printf("color %zu\n", scene->objs[i].color);
		printf("dir %f, %f, %f\n", scene->objs[i].dir.x, scene->objs[i].dir.y, scene->objs[i].dir.z);
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

void	free_yaml(t_yaml *lines, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(lines[i].value);
		free(lines[i].key);
		i++;
	}
}

void	parse_file(char *filename, t_scene *scene)
{
	int		fd;
	t_yaml	*lines;
	char	*line;
	size_t	i;

	lines = ft_memalloc(sizeof(t_yaml) * 100);
	(void)scene;
	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		perror("error");
		exit(1);
	}
	i = 0;
	while (get_next_line(fd, &line))
	{
		parse_line(line, lines + i);
		free(line);
		if (i > 998)
			fatal("file too large, fuck you" );
		i++;
	}
	close(fd);
	valid_yaml(lines, i);
//	debug(lines, i);
	parse_scene(lines, i, scene);
	free_yaml(lines, i);
	free(lines);
	debug_scene(scene);
//	exit(1);
}
