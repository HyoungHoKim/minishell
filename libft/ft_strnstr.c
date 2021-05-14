/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 21:27:46 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 18:21:49 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t			idx;
	size_t			l_len;
	size_t			b_len;

	if (!*little || !little)
		return ((char*)big);
	l_len = ft_strlen(little);
	b_len = ft_strlen(big);
	if (l_len > b_len || l_len > len)
		return (0);
	idx = 0;
	while (big[idx] != '\0' && idx <= len - l_len)
	{
		if (ft_strncmp(big + idx, little, l_len) == 0)
			return ((char*)big + idx);
		idx++;
	}
	return (0);
}
