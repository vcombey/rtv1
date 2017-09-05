#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

t_obj	*ft_new_obj(void)
{
	t_obj	*new;
	new = ft_memalloc(sizeof(t_obj));
	new->pos = ft_memalloc(sizeof(double) * 3);
	new->rot = ft_memalloc(sizeof(double) * 3);
	new->intersect = ft_memalloc(sizeof(double) * 3);
	new->norm = ft_memalloc(sizeof(double) * 3);
	return (new);
}

void	ft_obj_add(t_obj *new_node, t_obj **first)
{
	new_node->next = *first;
	*first = new_node;
}
