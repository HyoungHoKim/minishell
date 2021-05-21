/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:44:01 by seushin           #+#    #+#             */
/*   Updated: 2021/05/21 18:45:57 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

t_state		g_state;

int			check_double_semi(t_cmd *cmd)
{
	int		is_null;
	t_cmd	*temp;

	is_null = 0;
	temp = cmd;
	while (temp)
	{
		if (temp->token[0] == NULL)
		{
			if (is_null)
				return (FAILURE);
			is_null = 1;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

void		process(t_cmd *cmd)
{
	t_cmd	*temp;

	print_cmd_token(cmd);
	if (check_double_semi(cmd))
		return ;
	temp = cmd;
	while (temp)
	{
		if (temp->flag == 0)
			exec_command(temp->token);
		//else if (temp->flag == 1)
		//	exec_pipe(cmd);
		//else if (temp->flag == 2)
		//	exec_redir(cmd);
		temp = temp->next;
	}
}

static void	free_all(char *line, t_cmd *cmd)
{
	free(line);
	line = NULL;
	free_cmd(cmd);
	cmd = NULL;
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	if (init(&line, envp))
		return (FAILURE);
	while (1)
	{
		show_prompt();
		if (get_line(&line) < 1)
		{
			free(line);
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			exit(0);
		}
		cmd = create_cmd();
		if (parser(line, cmd))
			ft_putstr_fd("bash: error\n", STDOUT_FILENO);
		else
			process(cmd);
		free_all(line, cmd);
	}
	return (SUCCESS);
}
