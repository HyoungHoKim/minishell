/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 13:13:36 by seushin           #+#    #+#             */
/*   Updated: 2021/05/29 14:34:51 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/fcntl.h>

static char	**create_new_token(char **token)
{
	char	**res;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (token[i])
	{
		if (token[i][0] == '>' || token[i][0] == '<')
		{
			len++;
			i++;
		}
		i++;
	}
	if (len == 0)
		return (NULL);
	len = token_size(token) - len * 2;
	if (!(res = ft_calloc(sizeof(char *), len + 1)))
		return (NULL);
	return (res);
}

static int	cut_off_redirection(t_cmd *cmd)
{
	char	**res;
	int		i;
	int		j;

	if (!(res = create_new_token(cmd->token)))
		return (FAILURE);
	i = 0;
	j = 0;
	while (cmd->token[j])
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

static void	redirection_stdio(t_cmd *cmd, int fd[2])
{
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
}

static int	output_redirection(char **token, int i)
{
	int		fd;

	if (token[i][1] == '>')
		fd = open(token[i + 1], (O_CREAT | O_APPEND | O_WRONLY), 0644);
	else
		fd = open(token[i + 1], (O_CREAT | O_TRUNC | O_WRONLY), 0644);
	return (fd);
}

int			find_redirection(t_cmd *cmd)
{
	int		fd[2];
	int		i;

	ft_memset(fd, 0, sizeof(fd));
	i = -1;
	while (cmd->token[++i])
	{
		if (cmd->token[i][0] == '<')
		{
			if (fd[0] > 0)
				close(fd[0]);
			fd[0] = open(cmd->token[i + 1], O_RDONLY, 0644);
		}
		else if (cmd->token[i][0] == '>')
		{
			if (fd[1] > 0)
				close(fd[1]);
			fd[1] = output_redirection(cmd->token, i);
		}
		if (fd[0] == -1 || fd[1] == -1)
			return (handle_redirection_err(cmd, i));
	}
	redirection_stdio(cmd, fd);
	return (SUCCESS);
}
