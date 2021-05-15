/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/15 14:54:32 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_strncpy(char *dest, char const *src, unsigned int n)
{
	unsigned int	idx;

	idx = 0;
	while (idx < n && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}

void				set_cline(char const *str, int idx, int st, t_cline **head)
{
	char			*com_line;
	char			flag;

	flag = '\0';
	if (str[idx] == '|')
		flag = '|';
	else if (str[idx] == ';')
		flag = ';';
	com_line = (char*)malloc(sizeof(char) * (idx - st) + 1);
	ft_strncpy(com_line, str + st, (idx - st));
	com_line = del_side_space(com_line);
	cline_add_back(head, cline_new(com_line, flag));
}

void				command_seperate(char const *str, t_cline **head)
{
	int				idx;
	int				st;
	int				cnt;

	idx = 0;
	st = 0;
	cnt = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] != '|' && str[idx] != ';')
		{
			st = idx;
			while (str[idx] != '\0' && str[idx] != '|' && str[idx] != ';')
				idx++;
			set_cline(str, idx, st, head);
		}
		else
			idx++;
	}
	return ;
}

void				parser(t_cline **head, char *line)
{
	command_seperate(line, head);
	
}
