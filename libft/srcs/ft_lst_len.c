#include "libft.h"

size_t	ft_lst_len(t_list *lst)
{
	return (!lst ? 0 : 1 + ft_lst_len(lst->next));
}
