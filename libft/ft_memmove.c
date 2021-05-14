/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:38:43 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 16:04:38 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_d;
	unsigned char	*temp_s;
	int				idx;

	if (!dest && !src)
		return (0);
	idx = n - 1;
	temp_d = (unsigned char*)dest;
	temp_s = (unsigned char*)src;
	if (src < dest)
	{
		while (idx >= 0)
		{
			temp_d[idx] = temp_s[idx];
			idx--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
