/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:39:34 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 17:46:45 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int				get_chr_pos(char *line, char c)
{
	int			idx;

	idx = 0;
	while (line[idx] != '\0')
	{
		if (line[idx] == c)
			return (idx);
		idx++;
	}
	return (idx);
}

void			show_prompt(void)
{
	static char	*path;

	path = getcwd(path, MAXSIZE);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
}

void			print_cmd_token(t_cmd *cmd)
{
	int			idx;
	t_cmd		*temp;

	temp = cmd;
	while (temp)
	{
		idx = -1;
		printf("flag : %d\n", temp->flag);
		while (temp->token[++idx] != NULL)
			printf("token : %s\n", temp->token[idx]);
		temp = temp->next;
	}
}
