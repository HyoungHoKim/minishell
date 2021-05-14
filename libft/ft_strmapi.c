/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:06:17 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 22:21:56 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_ptr;
	int		idx;

	if (!s || !f)
		return (0);
	if (!(new_ptr = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	idx = 0;
	while (s[idx] != '\0')
	{
		new_ptr[idx] = f(idx, s[idx]);
		idx++;
	}
	new_ptr[idx] = '\0';
	return (new_ptr);
}
