#include "libft.h"

void	ft_arraydel(char ***tab)
{
	char	**tmp;

	tmp = *tab;
	while (*tmp)
	{
		ft_bzero(*tmp, ft_strlen(*tmp));
		ft_memdel((void*)tmp);
		tmp++;
	}
	free(*tab);
	*tab = NULL;
}
