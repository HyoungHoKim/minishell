/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkdemfp2 <dkdemfp2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 01:05:26 by dkdemfp2          #+#    #+#             */
/*   Updated: 2020/12/24 02:55:48 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	didx;
	size_t	sidx;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	didx = dest_len;
	sidx = 0;
	if (size <= dest_len)
		return (src_len + size);
	while ((src[sidx] != '\0') && sidx < (size - dest_len - 1))
		dest[didx++] = src[sidx++];
	dest[didx] = '\0';
	return (src_len + dest_len);
}
