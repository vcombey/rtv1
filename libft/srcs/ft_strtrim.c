#include "libft.h"
#include "str.h"

static	int		ft_char_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	start;
	size_t			len;

	i = 0;
	start = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i] && ft_char_is_space(s[i]))
		i++;
	start = i;
	while (s[i])
	{
		if (!(ft_char_is_space(s[i])))
			len = i - start + 1;
		i++;
	}
	return (ft_strsub(s, start, len));
}
