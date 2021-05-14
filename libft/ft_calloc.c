/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 01:21:13 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 20:41:05 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t nmemb, size_t size)
{
	void	*new_ptr;
	size_t	idx;

	if (!(new_ptr = (void *)malloc(nmemb * size)))
		return (0);
	idx = 0;
	while (idx < nmemb * size)
		((unsigned char*)new_ptr)[idx++] = 0;
	return (new_ptr);
}
