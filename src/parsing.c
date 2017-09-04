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
	new->value = ft_strtrim(sep + 1);
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

void	valid_yaml(t_yaml *lines, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len && i + 1 < len)
	{
//		printf("tab: %zu, key: %s, value: %s\n", lines[i+1].tab, lines[i+1].key, lines[i+1].value);
		if (lines[i].value[0] && (lines[i].tab != lines[i + 1].tab) && (lines[i].tab - 1 != lines[i + 1].tab))
			fatal("bad yaml");
		if (!lines[i].value[0] && lines[i].tab + 1 != lines[i + 1].tab)
			fatal("bad yaml");
		i++;
	}
}

void	debug_obj(t_obj *obj)
{
	t_obj	*tmp;

	tmp = obj;
	printf("tmp %zu\n", (size_t)tmp);
	while (tmp)
	{
		printf("name %s\n", tmp->name);
		printf("color %zu\n", tmp->color);
		printf("rot %f, %f, %f\n", tmp->rot[0], tmp->rot[1], tmp->rot[2]);
		printf("pos %f, %f, %f\n", tmp->pos[0], tmp->pos[1], tmp->pos[2]);
		printf("alpha %f\n", tmp->alpha);
		printf("rayon %f\n\n", tmp->rayon);
		tmp = tmp->next;
	}
}

void	debug_scene(t_scene *scene)
{
	printf("name %s\n", scene->name);
	printf("width %zu\n", scene->width);
	printf("height %zu\n", scene->height);
	printf("rot %f, %f, %f\n", scene->rot[0], scene->rot[1], scene->rot[2]);
	printf("campos %f, %f, %f\n", scene->cam.pos[0], scene->cam.pos[1], scene->cam.pos[2]);
	printf("camdir %f, %f, %f\n", scene->cam.dir[0], scene->cam.dir[1], scene->cam.dir[2]);
	debug_obj(scene->objs);
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
		i++;
	}
	close(fd);
	valid_yaml(lines, i);
	parse_scene(lines, i, scene);
	//debug(lines, i);
	//free yaml
	debug_scene(scene);
	exit(1);
}
