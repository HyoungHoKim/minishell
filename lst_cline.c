/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:11:08 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/13 16:32:31 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cline		*cline_new(char *com_line, char flag)
{
	t_cline	*new_node;

	if (!(new_node = (t_cline*)malloc(sizeof(t_cline))))
		return (0);
    new_node->flag = flag;
	new_node->com_line = com_line;
	new_node->next = 0;
	return (new_node);
}

void		cline_add_front(t_cline **lst, t_cline *new)
{
	if (!lst || !new)
		return ;
	else
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

void		cline_add_back(t_cline **lst, t_cline *new)
{
	t_cline	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void		cline_clear(t_cline **lst, void (*del)(void*))
{
	t_cline	*temp;
	t_cline	*next;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp)
	{
		next = temp->next;
		del(temp->com_line);
		free(temp);
		temp = next;
	}
	*lst = 0;
}

void        cline_print(t_cline *head)
{
    t_cline *temp;

    temp = head;
    while (temp != NULL)
    {
        printf("flag : [%c] com_line : [%s]\n", temp->flag, temp->com_line);
        temp = temp->next;
    }
}
