/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:40:13 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 19:07:10 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void		handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = waitpid(-1, &status, 0);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			show_new_line();
			g_state.my_errno = 1;
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			g_state.my_errno = status + 128;
		}
	}
	else if (signo == SIGQUIT && pid != -1)
	{
		printf("Quit: %d\n", status);
		g_state.my_errno = status + 128;
	}
}
