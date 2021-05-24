/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:40:13 by seushin           #+#    #+#             */
/*   Updated: 2021/05/23 17:56:01 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void		handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	// waitpid에서 첫번째 인자를 -1로 두고, WNOHANG을 옵션으로 두면 임의의 프로세스 중 어떤 프로세스라도
	// 종료되거나 멈추지 않았더라도 즉시 리턴하라는 의미
	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		// waitpid의 리턴값이 -1이면 자식 프로세스가 존재하지 않거나, 인터럽트시 반환
		if (pid == -1)
			show_new_line();
		else
			ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (signo == SIGQUIT)
	{
		if (pid == -1)
			show_new_line();
		else
			ft_putstr_fd("Quit...\n", STDOUT_FILENO);
	}
}
