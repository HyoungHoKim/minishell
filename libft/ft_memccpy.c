/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 01:45:10 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 14:40:31 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			idx;

	idx = 0;
	while (idx < n)
	{
		((unsigned char*)dest)[idx] = ((unsigned char*)src)[idx];
		if (((unsigned char*)dest)[idx] == (unsigned char)c)
			return (dest + idx + 1);
		idx++;
	}
	return (0);
}
