/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:45:46 by hyoukim           #+#    #+#             */
/*   Updated: 2020/12/23 16:53:10 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			revv(int *arr, int idx, bool check, int fd)
{
	int				i;

	i = idx;
	if (!check)
		ft_putchar_fd('-', fd);
	while (i >= 0)
	{
		ft_putchar_fd('0' + arr[i], fd);
		i--;
	}
}

void				ft_putnbr_fd(int n, int fd)
{
	int				arr[11];
	bool			check;
	int				idx;
	unsigned int	temp;

	idx = 0;
	temp = n;
	if (n < 0)
	{
		check = false;
		temp = -n;
	}
	else
		check = true;
	while (temp > 9)
	{
		arr[idx] = temp % 10;
		temp /= 10;
		idx++;
	}
	arr[idx] = temp;
	revv(arr, idx, check, fd);
}
