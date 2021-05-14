/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:05:53 by hhk               #+#    #+#             */
/*   Updated: 2020/12/25 21:10:48 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	size_t			idx;

	idx = 0;
	while (idx < n)
	{
		if (((unsigned char*)s)[idx] == (unsigned char)c)
			return ((void*)s + idx);
		idx++;
	}
	return (0);
}
