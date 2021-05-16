/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:58:25 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/16 15:08:39 by hyoukim          ###   ########.fr       */
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

int					init_cmd(char *line, t_cmd *cmd)
{
	char			*input;

	if (!(input = del_side_space(line))
		return (0);
	
}

int					parser(char *line, t_cmd *cmd)
{
	char			*input;


	//command_seperate(line, head);
	return (1);
}
