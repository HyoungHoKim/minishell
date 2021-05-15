/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoukim <hyoukim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 14:27:59 by hyoukim           #+#    #+#             */
/*   Updated: 2021/05/15 16:29:31 by seushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** line에서 찾아야 할 문자:
** 1. "
** 2. '
** 3. |
** 4. ;
** 5. >, >>, <
*/
char		**tokenizer(char *line)
{
	char	**res;

	res = NULL;
	while (*line)
	{
		if (*line != '\'' && *line != '\"')
			// 공백으로 문자 끝까지 잘라냄
			;
		else if (*line == '|' || *line == ';')
			// 파이프, 세미콜론, 리다이렉트일 경우 따로 처리
			;
		else
			// 해당하는 따옴표를 quote 배열에 넣고? 넣을 필요가 있나.
			// 같은 따옴표의 짝이 있는 곳까지 잘라냄.
			;
		// 잘라낸 토큰을 res에 하나씩 push함.
	}
	return (res);
}

int			parse(char *line, t_cmd *cmd)
{
	char	**token;

	token = tokenizer(line);
	//토큰 전처리 + 토큰을 파이프, 세미콜론 등을 기준으로 잘라냄
	//while문을 돌면서 토큰의 끝을 만날 때까지 커맨드 단위로 나눠서 생성
	//혹은 토크나이저가 커맨드 단위로 나눠줄 수도 있겠다.
	//free_strs(token);
	return (EXIT_SUCCESS);
}
