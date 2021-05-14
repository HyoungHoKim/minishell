/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:07:01 by hhk               #+#    #+#             */
/*   Updated: 2020/12/25 20:26:07 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		idx;

	idx = 0;
	while (idx < n)
	{
		if (((unsigned char*)s1)[idx] != ((unsigned char*)s2)[idx])
			return (((unsigned char*)s1)[idx] - ((unsigned char*)s2)[idx]);
		idx++;
	}
	return (0);
}
