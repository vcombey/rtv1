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
		fatal("parse error");
	if (ft_strchr(sep + 1, ':'))
		fatal("parse error");
	*sep = '\0';
	new->key = ft_strdup(line);
	new->value = ft_strdup(sep + 1);
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
		printf("tab: %zu, key: %s, value: %s\n", lines[i+1].tab, lines[i+1].key, lines[i+1].value);
		if (lines[i].value[0] && (lines[i].tab != lines[i + 1].tab) && (lines[i].tab - 1 != lines[i + 1].tab))
			fatal("parse error");
		if (!lines[i].value[0] && lines[i].tab + 1 != lines[i + 1].tab)
			fatal("parse error");
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
		i++;
	}
	close(fd);
	valid_yaml(lines, i);
	parse_scene(lines, i, scene);
	debug(lines, i);
	exit(1);
}



