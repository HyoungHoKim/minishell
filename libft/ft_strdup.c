/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:16:33 by hyoukim           #+#    #+#             */
/*   Updated: 2020/12/30 14:23:38 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*dest;
	int		len;
	int		idx;

	len = ft_strlen(s1);
	if (!(dest = (char *)malloc(len + 1)))
		return (0);
	idx = 0;
	while (s1[idx] != '\0')
	{
		dest[idx] = s1[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}
