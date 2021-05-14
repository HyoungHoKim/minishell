#include "minishell.h"

char		**copy_envp(char **envs)
{
	char	**new;
	int		i;

	i = 0;
	while (envs[i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = -1;
	while (envs[++i] != NULL)
		new[i] = ft_strdup(envs[i]);
	new[i] = NULL;
	return (new);
}