#include "libft.h"
#include "list.h"

void	ft_simple_lst_remove(t_list **first, void (*f)(void*))
{
	t_list	*node;
	t_list	*tmp_next;

	node = *first;
	while (node)
	{
		tmp_next = node->next;
		ft_simple_lst_del_one(first, node, (f));
		node = tmp_next;
	}
	*first = NULL;
}

void	ft_double_lst_remove(t_lst_head **head, void (*f)(void*))
{
	t_list_d	*curr;
	t_list_d	*next;

	curr = ((*head)->first);
	while (curr)
	{
		next = curr->next;
		if (curr->data && f)
			(f)(curr->data);
		free(curr);
		curr = next;
	}
	(*head)->first = NULL;
	(*head)->middle = NULL;
	(*head)->last = NULL;
}

void	ft_remove_head(t_lst_head **head, void (*f)(void*))
{
	ft_double_lst_remove(head, (f));
	free(*head);
	*head = NULL;
}
