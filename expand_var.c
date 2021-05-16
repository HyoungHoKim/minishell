#include "libft/libft.h"
#include "minishell.h"

static int	get_dollar_idx(char *buf)
{
	char	*dolr_loc;

	if ((dolr_loc = ft_strchr(buf, '$')))
		return (dolr_loc - buf);
	return (-1);
}

static int	get_var_len(char *buf)
{
	int		len;
	int		i;

	len = 0;
	i = 1;
	while (buf[i] == '_' || ft_isalnum(buf[i]))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*get_var(char *buf)
{
	char	*key;
	char	*value;
	int		len;

	len = get_var_len(buf);
	key = ft_substr(buf, 1, len);
	if ((value = get_env_value(key)))
		value = ft_strdup(value);
	else
		value = ft_strdup("");
	free(key);
	return (value);
}

static char	**split_buf(char *buf)
{
	char	**token;
	int		sub_len;
	int		dollar_idx;

	token = create_token();
	while (*buf)
	{
		if ((dollar_idx = get_dollar_idx(buf)) != -1)
			sub_len = dollar_idx;
		else
			sub_len = ft_strlen(buf);
		token_push_back(&token, ft_substr(buf, 0, sub_len));
		buf += sub_len;
		if (dollar_idx != -1)
		{
			token_push_back(&token, get_var(buf));
			buf += get_var_len(buf) + 1;
		}
	}
	return (token);
}

static int	get_total_len(char **token)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (token[i])
	{
		len += ft_strlen(token[i]);
		i++;
	}
	return (len);
}

char		*expand_var(char *buf)
{
	char	*res;
	char	**token;
	int		len;
	int		i;

	token = split_buf(buf);
	len = get_total_len(token);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[0] = '\0';
	i = -1;
	while (token[++i])
		ft_strlcat(res, token[i], len + 1);
	free_token(token);
	return (res);
}
