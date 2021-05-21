/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:17:09 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/21 18:47:27 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_home_dir(void)
{
	char	*home_dir;

	home_dir = ft_strdup(get_env_value("HOME"));
	return (home_dir);
}

int			ft_cd(char **token)
{
	char	*dir;
	int		is_go;

	if (token_size(token) == 1)
		dir = get_home_dir();
	else
	{
		if (ft_strncmp(token[1], "~", ft_strlen(token[1])) == 0)
			dir = get_home_dir();
		else
			dir = ft_strdup(token[1]);
	}
	is_go = chdir(dir);
	free(dir);
	if (is_go == -1)
		return (FAILURE);
	return (SUCCESS);
}
