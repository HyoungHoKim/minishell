/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkdemfp2 <dkdemfp2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 21:29:20 by dkdemfp2          #+#    #+#             */
/*   Updated: 2020/12/30 14:27:25 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	idx;
	size_t	cnt;

	idx = 0;
	cnt = 0;
	if (!src)
		return (0);
	while (src[cnt] != '\0')
		cnt++;
	if (!dest || size == 0)
		return (cnt);
	while (src[idx] != '\0' && idx + 1 < size)
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (cnt);
}
