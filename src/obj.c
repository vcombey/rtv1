#include "rt.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	ft_obj_add(t_obj *new_node, t_obj **first)
{
	new_node->next = *first;
	*first = new_node;
}
