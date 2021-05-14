/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:14:53 by hhk               #+#    #+#             */
/*   Updated: 2020/12/27 20:18:22 by hhk              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *lst)
{
	int		cnt;
	t_list	*temp;

	if (!lst)
		return (0);
	cnt = 0;
	temp = lst;
	while (temp != NULL)
	{
		cnt++;
		temp = temp->next;
	}
	return (cnt);
}
