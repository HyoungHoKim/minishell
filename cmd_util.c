#include "minishell.h"

t_cmd		*create_cmd(void)
{
	t_cmd	*res;

	res = ft_calloc(sizeof(t_cmd), 1);
	if (!res)
		return (NULL);
	res->token = create_token();
	if (!res->token)
	{
		free(res);
		res = NULL;
	}
	return (res);
}
