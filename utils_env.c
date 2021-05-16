#include "minishell.h"

char		**copy_envp(char **envp)
{
	char	**res;
	int		size;
	int		i;

	size = token_size(envp);
	if (!(res = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = ft_strdup(envp[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char		*get_env(char *key)
{
	int		size;
	int		i;

	size = ft_strlen(key);
	i = 0;
	while (g_state.env[i])
	{
		if (ft_strncmp(g_state.env[i], key, size) == 0 &&
				g_state.env[i][size] == '=')
			return (g_state.env[i]);
		i++;
	}
	return (NULL);
}
