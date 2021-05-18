#include "minishell.h"

int			set_semi_pipe(char c)
{
	if (c == ';')
		return (SEMI);
	return (PIPE);
}
