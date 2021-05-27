/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seushin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:43:20 by seushin           #+#    #+#             */
/*   Updated: 2021/05/27 17:48:03 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	get_dollar_idx(char *buf)
{
	char	*dolr_loc;

	if ((dolr_loc = ft_strchr(buf, '$')))
	{
		if (is_set(*(dolr_loc + 1), " /%^=") || *(dolr_loc + 1) == '\0')
			return (-1);
		if (buf <= (dolr_loc - 1) && *(dolr_loc - 1) == '\\')
			return (get_dollar_idx(dolr_loc + 1));
		return (dolr_loc - buf);
	}
	return (-1);
}

static int	find_backslash(char *buf)
{
	char	*backslash;
	char	*next_char;

	if ((backslash = ft_strchr(buf, '\\')))
	{
		next_char = backslash + 1;
		if (is_set(*next_char, "\\\'\"`$"))
			return (backslash - buf);
	}
	return (-1);
}

int			get_split_idx(char *buf, int *bs_idx, int *dr_idx)
{
	if ((*bs_idx = find_backslash(buf)) != -1)
		return (*bs_idx);
	else if ((*dr_idx = get_dollar_idx(buf)) != -1)
		return (*dr_idx);
	else
		return (ft_strlen(buf));
}
