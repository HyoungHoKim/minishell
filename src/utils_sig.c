/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:40:13 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 18:42:03 by seushin          ###   ########.fr       */
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
			g_state.errno = 1;
		}
		else
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			g_state.errno = status + 128;
		}
	}
	else if (signo == SIGQUIT)
	{
		if (pid != -1)
		{
			ft_putstr_fd("Quit: ", STDOUT_FILENO);
			ft_putnbr_fd(status, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			g_state.errno = status + 128;
		}
	}
}
