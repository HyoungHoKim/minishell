/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:17:09 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/30 15:08:45 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		change_pwd_env(void)
{
	char	*dir;
	char	*temp;

	if (!(get_env("PWD")))
		dir = ft_strdup("");
	else
		dir = ft_strdup(get_env_value("PWD"));
	temp = ft_strjoin("OLDPWD=", dir);
	if (!(get_env("OLDPWD")))
		token_push_back(&g_state.env, temp);
	else
		replace_env(temp, "OLDPWD");
	free(temp);
	free(dir);
	dir = getcwd(NULL, 0);
	temp = ft_strjoin("PWD=", dir);
	if (!(get_env("PWD")))
		token_push_back(&g_state.env, ft_strdup(temp));
	else
		replace_env(temp, "PWD");
	free(dir);
	free(temp);
}

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
		return (err_msg_builtin(token[0], "HOME not set", 1));
	is_go = chdir(dir);
	free(dir);
	if (is_go == -1)
		return (err_msg(token[0], token[1], "No such file or directory", 1));
	else
		change_pwd_env();
	g_state.my_errno = SUCCESS;
}
