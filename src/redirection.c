/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:13:36 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 14:14:38 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/fcntl.h>

static char	**create_new_token(char **token, int *len)
{
	char	**res;
	int		i;

	*len = 0;
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '>' || token[i][0] == '<')
		{
			(*len)++;
			i++;
		}
		i++;
	}
	if (*len == 0)
		return (NULL);
	*len = token_size(token) - *len * 2;
	if (!(res = ft_calloc(sizeof(char *), *len + 1)))
		return (NULL);
	return (res);
}

static int	cut_off_redirection(t_cmd *cmd)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	if (!(res = create_new_token(cmd->token, &len)))
		return (FAILURE);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (cmd->token[j] &&
				(cmd->token[j][0] == '>' || cmd->token[j][0] == '<'))
		{
			free(cmd->token[j++]);
			free(cmd->token[j]);
		}
		else
			res[i++] = cmd->token[j];
		j++;
	}
	free(cmd->token);
	cmd->token = res;
	return (SUCCESS);
}

static int	dup_fd_to_stdio(t_cmd *cmd, int fd[2])
{
	if (fd[0] == -1 || fd[1] == -1)
		return (FAILURE);
	if (fd[0])
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1])
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	cut_off_redirection(cmd);
	return (SUCCESS);
}

int			find_redirection(t_cmd *cmd)
{
	char	**token;
	int		fd[2];
	int		i;

	token = cmd->token;
	ft_memset(fd, 0, sizeof(fd));
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '<')
			fd[0] = open(token[i + 1], O_RDONLY, 0644);
		else if (token[i][0] == '>')
		{
			if (token[i][1] == '>')
				fd[1] = open(token[i + 1],
						(O_CREAT | O_APPEND | O_WRONLY), 0644);
			else
				fd[1] = open(token[i + 1],
						(O_CREAT | O_TRUNC | O_WRONLY), 0644);
		}
		i++;
	}
	return (dup_fd_to_stdio(cmd, fd));
}
