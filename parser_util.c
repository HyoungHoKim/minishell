#include "minishell.h"

int			get_flag(char c)
{
	if (c == ';')
		return (SEMI);
	return (PIPE);
}
