/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkdemfp2 <dkdemfp2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 02:25:10 by dkdemfp2          #+#    #+#             */
/*   Updated: 2020/12/28 22:36:29 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	getnum(const char *str, int i, int minus)
{
	int				idx;
	long long		num;

	idx = i;
	num = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		num = num * 10 + (str[idx] - '0');
		if (num > 2147483647 && minus == 1)
			return (-1);
		if (num > 2147483648 && minus == -1)
			return (0);
		idx++;
	}
	return (num);
}

int					ft_atoi(const char *str)
{
	long long		num;
	int				idx;
	int				minus;

	num = 0;
	idx = 0;
	minus = 1;
	while (str[idx] == ' ' || (str[idx] >= '\t' && str[idx] <= '\r'))
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
	{
		if (str[idx] == '-')
			minus = -1;
		idx++;
	}
	if (str[idx] >= '0' && str[idx] <= '9')
		num = getnum(str, idx, minus);
	return (num * minus);
}
