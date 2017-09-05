#include "libft.h"
#include <unistd.h>

void	ft_putstrstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putendl(str[i]);
		i++;
	}
}
