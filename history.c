/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <seushin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 17:19:47 by seushin           #+#    #+#             */
/*   Updated: 2021/05/23 17:59:53 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void		free_hist(t_hist *hist)
{
	free(hist->line);
	hist->line = NULL;
	free(hist);
}

void		hist_pop_front(t_hist **head)
{
	t_hist	*next_hist;

	if (!*head)
		return ;
	while ((*head)->prev)
		(*head) = (*head)->prev;
	next_hist = (*head)->next;
	free_hist(*head);
	*head = next_hist;
	if (*head)
		(*head)->prev = NULL;
}

void		hist_push_front(t_hist **head, char *line)
{
	t_hist	*new_hist;

	if ((new_hist = (t_hist *)malloc(sizeof(t_hist))))
	{
		new_hist->prev = NULL;
		new_hist->next = *head;
		if (*head)
			(*head)->prev = new_hist;
		new_hist->line = ft_strdup(line);
	}
	*head = new_hist;
}

/*
** 만약 히스토리가 존재한다면,
** 현재 line을 모두 지우고(커서도 동시에 이동하면서)
** 히스토리의 라인을 터미널에 출력하며, line 버퍼에도 복사한다.
*/

void		print_next_hist(t_hist **hist, t_input *input)
{
	int		i;

	if (!*hist)
	{
		*hist = g_state.hist;
		hist_push_front(hist, input->buf);
	}
	if (!(*hist)->next)
		return ;
	*hist = (*hist)->next;
	while (input->x)
		handle_backspace(input);
	i = 0;
	while ((*hist)->line[i])
		handle_insert(input, (*hist)->line[i++]);
}

void		print_prev_hist(t_hist **hist, t_input *input)
{
	int		i;

	if (!*hist || !(*hist)->prev)
		return ;
	*hist = (*hist)->prev;
	while (input->x)
		handle_backspace(input);
	i = 0;
	while ((*hist)->line[i])
		handle_insert(input, (*hist)->line[i++]);
}
