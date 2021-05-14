/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 18:29:35 by hhk               #+#    #+#             */
/*   Updated: 2020/12/28 22:37:30 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		getsize(long long n)
{
	int			size;

	size = 1;
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char		*inputnum(long long n, int len, bool isminus)
{
	char		*answer;

	if (!(answer = (char*)malloc(sizeof(char) * len + 1)))
		return (0);
	answer[len] = '\0';
	len = len - 1;
	while (len >= 0 && n >= 10)
	{
		answer[len] = '0' + (n % 10);
		n /= 10;
		len--;
	}
	if (isminus)
	{
		answer[0] = '-';
		answer[1] = '0' + n;
	}
	else
		answer[0] = '0' + n;
	return (answer);
}

char			*ft_itoa(int n)
{
	char		*answer;
	int			len;
	bool		isminus;
	long long	num;

	num = n;
	if (num < 0)
	{
		num *= -1;
		len = getsize(num) + 1;
		isminus = true;
	}
	else
	{
		len = getsize(num);
		isminus = false;
	}
	answer = inputnum(num, len, isminus);
	return (answer);
}
