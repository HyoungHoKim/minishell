/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:17:09 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/17 21:17:05 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			move_home_dir(void)
{
	char	*home_dir;

	home_dir = get_env_value("HOME");
	if (chdir(home_dir) == -1)
		return (FAILURE);
	return (SUCCESS);
}

char		*get_before_dir()
{
	char	*buf;
	char	*before_dir;
	int		len;

	buf = NULL;
	buf = getcwd(buf, 0);
	len = ft_strlen(buf);
	if (len == 1)
		return (buf);
	while (buf[--len])
	{
		if(buf[len] == '/')
		{
			if (len == 0)
				return (ft_substr(buf, 0, 1));
			before_dir = ft_substr(buf, 0, len);
			break ;
		}
	}
	free(buf);
	return (before_dir);
}

int			move_dir_free(char *dir)
{
	int		is_go;
	
	is_go = chdir(dir);
	free(dir);
	if (is_go == -1)
		return (FAILURE);
	return (SUCCESS);
}

int			ft_cd(char **token)
{
	if (token_size(token) == 1)
	{
		if(move_home_dir())
			return (FAILURE);
	}
	else
	{
		if(ft_strncmp(token[1], "~", ft_strlen(token[1])) == 0)
			if(move_home_dir())
				return (FAILURE);
		if(ft_strncmp(token[1], "..", ft_strlen(token[1])) == 0)
			if (move_dir_free(get_before_dir()))
				return (FAILURE);
	}
	return (SUCCESS);
}