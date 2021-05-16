/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:27:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/14 16:54:13 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_command(char **new, char *com_line)
{
	int		pos;
	char	*cut_command;

	pos = get_chr_pos(com_line, ' ');
	cut_command = ft_substr(com_line, 0, pos);
	*new = ft_strjoin("/bin/", cut_command);
	free(cut_command);
	return (com_line);
}

char		*get_option(char **new, char *option)
{
	int		pos;
	char	*temp;

	pos = get_chr_pos(option, ' ');
	if (option[0] == '-')
	{
		*new = ft_substr(option, 0, pos);
		temp = ft_substr(option, pos + 1, ft_strlen(option) - pos);
		free(option);
	}
	else
		temp = option;
	return (temp);
}

void		tokenizer(t_cline **head)
{
	t_cline	*temp;
	char	*com_line;

	temp = *head;
	while (temp != NULL)
	{
		temp->token = (char**)malloc(sizeof(char*) * 1)
		com_line = ft_strdup(temp->com_line);
		com_line = get_command(&temp->token.command, com_line);
		printf("command : %s\n", temp->token.command);
		//com_line = get_option(&temp->token.option, com_line);
		//temp->token.data = ft_strdup(com_line);
		temp = temp->next;
		free(com_line);
	}
}
