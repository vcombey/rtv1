#include "libft.h"

static float	ft_strtof_get_number(char *str, char **end_ptr, float r)
{
	while (*str && ft_isdigit(*str))
	{
		r = r * 10 + *str - '0';
		str++;
	}
	if (*str == '.')
	{
		str++;
		float	dec_exp;
		dec_exp = 1;
		while (*str && ft_isdigit(*str))
		{
			dec_exp = dec_exp / 10;
			r += (*str - '0') * dec_exp;
			str++;
		}
	}
	*end_ptr = str;
	return (r);
}

int		ft_strtof(char *str, char **end_ptr, float *res)
{
	float r;
	int neg;

	r = 0;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg *= -1;
		str++;
	}
	if (!(ft_isdigit(*str)))
		return (0);
	r = ft_strtof_get_number(str, end_ptr, r);
	*res = r * neg;
	return (1);
}

