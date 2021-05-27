/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:17:09 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/27 20:27:14 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_home_dir(void)
{
	char	*home_dir;
	char	*value;

	if (!(value = get_env_value("HOME")))
		return (NULL);
	home_dir = ft_strdup(value);
	return (home_dir);
}

void		ft_cd(char **token)
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
	if (dir == NULL)
	{
		err_msg_builtin(token[0], "HOME not set", 1);
		return ;
	}
	is_go = chdir(dir);
	free(dir);
	if (is_go == -1)
	{
		err_msg(token[0], token[1], "No such file or directory", 1);
		return ;
	}
	g_state.my_errno = SUCCESS;
}
