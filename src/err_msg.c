/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 15:37:42 by seushin           #+#    #+#             */
/*   Updated: 2021/05/25 17:52:39 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int		err_msg(char *err_type, char *comment, int errno)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(err_type, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(comment, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	g_state.errno = errno;
	return (FAILURE);
}
