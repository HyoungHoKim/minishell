/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:34:55 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/17 18:45:00 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pwd(void)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 0);
	ft_putstr_fd(buf, STDIN);
	ft_putstr_fd("\n", STDIN);
	free(buf);
}