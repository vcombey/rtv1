/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 02:55:52 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/04 22:53:11 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *a)
{
	int res;
	int i;
	int neg;

	res = 0;
	i = 0;
	neg = 1;
	while (a[i] == ' ' || (a[i] >= 9 && a[i] <= 13))
		i++;
	if (a[i] == '-' || a[i] == '+')
	{
		if (a[i] == '-')
			neg *= -1;
		i++;
	}
	while (a[i] && ft_isdigit(a[i]))
	{
		res = res * 10 + a[i] - '0';
		i++;
	}
	return (res * neg);
}
