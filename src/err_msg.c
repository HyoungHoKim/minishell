/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:37:42 by seushin           #+#    #+#             */
/*   Updated: 2021/05/26 13:50:07 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		err_msg(char *command, char *err_type, char *comment, int my_errno)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_state.my_errno = my_errno;
	return (FAILURE);
}

int		err_msg_export(char *command, char *err_type, char *comment, int my_errno)
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
	return (FAILURE);
}

int		err_msg_extern(char *err_type, char *comment)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (FAILURE);
}