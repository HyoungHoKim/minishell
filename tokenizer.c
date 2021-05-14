/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:27:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/14 12:44:25 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 		*get_command(char **new, char *com_line)
{
	int		pos;
	char	*temp;

	pos = get_chr_pos(com_line, ' ');
	*new = (char*)malloc(sizeof(char) * pos + 1);
	if (ft_strncmp("echo", com_line, pos) == 0)
		ft_strlcpy(*new, "echo", pos + 1);
	else if (ft_strncmp("cd", com_line, pos) == 0)
		ft_strlcpy(*new, "cd", pos + 1);
	else if (ft_strncmp("pwd", com_line, pos) == 0)
		ft_strlcpy(*new, "pwd", pos + 1);
	else if (ft_strncmp("export", com_line, pos) == 0)
		ft_strlcpy(*new, "export", pos + 1);
	else if (ft_strncmp("unset", com_line, pos) == 0)
		ft_strlcpy(*new, "env", pos + 1);
	else if (ft_strncmp("env", com_line, pos) == 0)
		ft_strlcpy(*new, "exit", pos + 1);
	temp = ft_substr(com_line, pos + 1, ft_strlen(com_line) - pos);
	free(com_line);
	return (temp);
}

/*
char		get_option(char **new, char *option)
{
	int		pos;
	char	temp; 

	pos = get_chr_pos(com_line, ' ');
	if (ft_strncmp("-n", option, pos) == 0)
		*new = ft_substr(option, 0, pos + 1);
	temp = ft_substr(option, pos + 1)
}
*/

void		tokenizer(t_cline **head)
{
    t_cline *temp;
	char	*com_line;

	temp = *head;
	while (temp != NULL)
	{
		com_line = ft_strdup(temp->com_line);
		com_line = get_command(&temp->token.command, com_line);
		
		temp = temp->next;
		free(com_line);
	}
}