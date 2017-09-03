/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 12:42:28 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 12:42:30 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H
# include <stdlib.h>

/*
**	In file palloc.c
*/

void	*palloc(size_t size);

/*
**	In file ft_memalloc.c
*/

void	*ft_memalloc(size_t size);

/*
**	In file ft_calloc.c
*/

void	*ft_calloc(size_t count, size_t size);

/*
**	in file ft_realloc.c
*/

void	*ft_realloc(size_t	curr_size, void *ptr, size_t new_size);
void	*cl_realloc(size_t	curr_size, void *ptr, size_t new_size);
#endif
