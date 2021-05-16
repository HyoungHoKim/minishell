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

t_cmd		*rewind_cmd(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	return (cmd);
}

void		free_cmd(t_cmd *cmd)
{
	t_cmd	*prev;

	while (cmd)
	{
		free_token(cmd->token);
		prev = cmd;
		cmd = cmd->next;
		free(prev);
	}
}
