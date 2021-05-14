/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 01:23:05 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 14:25:23 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			idx;

	idx = 0;
	if (!dest && !src)
		return (0);
	while (idx < n)
	{
		((unsigned char*)dest)[idx] = ((unsigned char*)src)[idx];
		idx++;
	}
	return (dest);
}
