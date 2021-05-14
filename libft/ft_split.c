/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:03:54 by hyoukim           #+#    #+#             */
/*   Updated: 2020/12/28 22:39:44 by hyoukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				*ft_strncpy(char *dest, char const *src, unsigned int n)
{
	unsigned int		idx;

	idx = 0;
	while (idx < n && src[idx] != '\0')
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = '\0';
	return (dest);
}

static char				**ft_seperate(char **ans, char const *str, char c)
{
	int					idx;
	int					st;
	int					cnt;

	idx = 0;
	st = 0;
	cnt = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] != c)
		{
			st = idx;
			while (str[idx] != '\0' && str[idx] != c)
				idx++;
			if (!(ans[cnt] = (char*)malloc(sizeof(char) * (idx - st) + 1)))
				return (0);
			ft_strncpy(ans[cnt++], str + st, (idx - st));
		}
		else
			idx++;
	}
	return (ans);
}

static char				**malloc_error(char **ans)
{
	while (!(*ans))
		free(*ans++);
	free(ans);
	return (0);
}

char					**ft_split(char const *s, char c)
{
	char				**ans;
	int					idx;
	int					splitcnt;

	if (!s)
		return (0);
	idx = 0;
	splitcnt = 0;
	while (s[idx])
	{
		if (s[idx] != c)
		{
			splitcnt++;
			while (s[idx] && s[idx] != c)
				idx++;
		}
		else
			idx++;
	}
	if (!(ans = (char**)malloc(sizeof(char*) * (splitcnt + 1))))
		return (0);
	if (!(ft_seperate(ans, s, c)))
		return (malloc_error(ans));
	ans[splitcnt] = 0;
	return (ans);
}
