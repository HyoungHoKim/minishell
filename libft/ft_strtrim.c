/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhk <hhk@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:13:55 by hhk               #+#    #+#             */
/*   Updated: 2020/12/31 17:23:29 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		starttrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	size_t		start;

	i = 0;
	start = 0;
	while (i < ft_strlen(s1))
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				start++;
				break ;
			}
			j++;
		}
		if (j == ft_strlen(set))
			break ;
		i++;
	}
	return (start);
}

static int		endtrim(char const *s1, char const *set)
{
	int			i;
	size_t		j;
	size_t		end;

	i = ft_strlen(s1) - 1;
	end = ft_strlen(s1);
	while (i >= 0)
	{
		j = 0;
		while (j < ft_strlen(set))
		{
			if (s1[i] == set[j])
			{
				end--;
				break ;
			}
			j++;
		}
		if (j == ft_strlen(set))
			break ;
		i--;
	}
	return (end);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char		*new_ptr;
	int			start;
	int			end;
	int			ptrlen;

	if (!s1)
		return (0);
	if (!set)
		return ((char*)s1);
	start = starttrim(s1, set);
	if (start == (int)ft_strlen(s1))
		return (ft_strdup(""));
	end = endtrim(s1, set);
	ptrlen = ft_strlen(s1) - start - (ft_strlen(s1) - end);
	new_ptr = ft_substr(s1, start, ptrlen);
	return (new_ptr);
}
