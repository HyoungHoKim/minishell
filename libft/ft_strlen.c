/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:36:31 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/27 20:13:17 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *str)
{
	size_t	idx;

	if (str == NULL)
		return (0);
	idx = 0;
	while (str[idx] != '\0')
		idx++;
	return (idx);
}
