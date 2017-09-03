/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:42:28 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:42:31 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H
# include <string.h>

size_t		ft_arraylen(const char **str);
/*
** In file arraydup.c
*/

char		**ft_arraydup(const char **original);

void		ft_arraydel(char ***tab);
const char	**ft_arraychr(const char **array, const char *str);
size_t		ft_arraymax_f(char **str, size_t (*f)(char *));
#endif
