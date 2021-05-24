/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 21:07:51 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/23 16:25:56 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			exec_command(char **token)
{
	if (token[0] == NULL)
		return (SUCCESS);
	else if (check_builtin(token))
		exec_builtin(token);
	else
		extern_func(token);
	return (SUCCESS);
}
