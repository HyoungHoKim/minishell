/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 15:21:49 by hyoukim           #+#    #+#             */
/*   Updated: 2020/12/30 14:28:26 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(const char *s1, const char *s2)
{
	char		*temp;
	int			totalsize;
	int			idx;
	int			i;

	if (!s1 || !s2)
		return (0);
	totalsize = 0;
	idx = 0;
	i = 0;
	totalsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(temp = (char *)malloc(sizeof(char) * totalsize)))
		return (0);
	while (s1[idx] != '\0')
	{
		temp[idx] = s1[idx];
		idx++;
	}
	while (s2[i] != '\0')
		temp[idx++] = s2[i++];
	temp[totalsize - 1] = '\0';
	return (temp);
}
