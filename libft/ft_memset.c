/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 23:49:47 by hyoukim           #+#    #+#             */
/*   Updated: 2020/12/25 17:11:08 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *ptr, int value, size_t num)
{
	size_t			idx;

	idx = 0;
	while (idx < num)
		((unsigned char *)ptr)[idx++] = (unsigned char)value;
	return (ptr);
}
