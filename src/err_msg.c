/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:37:42 by seushin           #+#    #+#             */
/*   Updated: 2021/05/30 15:01:54 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	err_msg(char *command, char *err_type, char *comment, int my_errno)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_state.my_errno = my_errno;
}

void	err_msg_export(
		char *command, char *err_type, char *comment, int my_errno)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_state.my_errno = my_errno;
}

void	err_msg_builtin(char *err_type, char *comment, int my_errno)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_state.my_errno = my_errno;
}

void	err_msg_extern(char *err_type, char *comment)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	err_msg_multiline(int my_errno)
{
	ft_putstr_fd("bash: Not support multiline\n", STDERR_FILENO);
	g_state.my_errno = my_errno;
}
