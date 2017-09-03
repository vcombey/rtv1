#include "libft.h"
#include "list.h"

void	ft_simple_lst_del_one(t_list **first, t_list *node, void (*f)(void*))
{
	t_list	*old_tmp;
	t_list	*curr_tmp;

	if (node)
	{
		curr_tmp = *first;
		old_tmp = curr_tmp;
		while (curr_tmp && curr_tmp != node)
		{
			old_tmp = curr_tmp;
			curr_tmp = curr_tmp->next;
		}
		if (*first == node)
			*first = node->next;
		else
			old_tmp->next = curr_tmp->next;
		if (f)
			(f)(node->data);
		free(node);
	}
}
