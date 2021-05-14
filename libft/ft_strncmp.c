/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 00:47:23 by dkdemfp2          #+#    #+#             */
/*   Updated: 2020/12/30 14:27:55 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	idx;
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	temp_s1 = (unsigned char*)s1;
	temp_s2 = (unsigned char*)s2;
	idx = 0;
	while (idx < n && (temp_s1[idx] != '\0' || temp_s2[idx] != '\0'))
	{
		if (temp_s1[idx] > temp_s2[idx])
			return (1);
		else if (temp_s1[idx] < temp_s2[idx])
			return (-1);
		idx++;
	}
	return (0);
}
