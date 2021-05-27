/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:16:33 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/27 20:15:19 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*dest;
	int		len;
	int		idx;

	if (s1 == NULL)
		return (NULL);
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
