/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:38:04 by hhk               #+#    #+#             */
/*   Updated: 2020/12/30 13:54:08 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	size_t		i;
	size_t		j;
	size_t		slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	i = start;
	j = 0;
	if (!(sub = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < slen && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
