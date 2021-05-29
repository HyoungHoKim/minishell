/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extern.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:17:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/29 12:48:14 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_dir_token(char *token)
{
	if (token[0] == '/')
		return (1);
	else if (ft_strncmp(token, "./", 2) == 0)
		return (1);
	else
		return (0);
}

char		*find_extern_dir(char *token)
{
	char		**path_list;
	char		**head;
	char		*dir;
	struct stat	sb;

	if (check_dir_token(token))
		return (token);
	if ((path_list = ft_split(get_env_value("PATH"), ':')) == NULL)
		return (token);
	head = path_list;
	token = ft_strjoin("/", token);
	while (*path_list != NULL)
	{
		dir = ft_strjoin(*path_list, token);
		if (stat(dir, &sb) == 0)
			break ;
		free(*path_list);
		free(dir);
		path_list++;
	}
	free(head);
	free(token);
	if (stat(dir, &sb) != 0)
		return (NULL);
	return (dir);
}

int			exec_extern(t_cmd *cmd)
{
	int		ret;
	char	*path;

	if ((path = find_extern_dir(cmd->token[0])) == NULL)
	{
		err_msg_extern(cmd->token[0], "command not found");
		exit(127);
	}
	ret = execve(path, cmd->token, g_state.env);
	return (ret);
}
