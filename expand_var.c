#include "libft/libft.h"
#include "minishell.h"

static int	is_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int	get_dollar_idx(char *buf)
{
	char	*dolr_loc;

	if ((dolr_loc = ft_strchr(buf, '$')))
	{
		if (*(dolr_loc + 1) == '\0' || *(dolr_loc + 1) == ' ')
			return (-1);
		if (buf <= (dolr_loc - 1) && *(dolr_loc - 1) == '\\')
			return (get_dollar_idx(dolr_loc + 1));
		return (dolr_loc - buf);
	}
	return (-1);
}

static int	get_var_len(char *buf)
{
	int		len;
	int		i;

	len = 0;
	i = 1;
	if (ft_isdigit(buf[i]) || buf[i] == '$')
		return (1);
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

static int	find_backslash(char *buf)
{
	char	*backslash;
	char	*next_char;

	if ((backslash = ft_strchr(buf, '\\')))
	{
		next_char = backslash + 1;
		if (is_set(*next_char, "\\\'\"`$"))
			return (backslash - buf);
	}
	return (-1);
}

static char	**split_buf(char *buf)
{
	char	**token;
	int		sub_len;
	int		dollar_idx;
	int		backslash_idx;

	token = create_token();
	while (*buf)
	{
		if ((backslash_idx = find_backslash(buf)) != -1)
			sub_len = backslash_idx;
		else if ((dollar_idx = get_dollar_idx(buf)) != -1)
			sub_len = dollar_idx;
		else
			sub_len = ft_strlen(buf);
		token_push_back(&token, ft_substr(buf, 0, sub_len));
		buf += sub_len;
		if (backslash_idx != -1)
		{
			token_push_back(&token, ft_substr(buf, 1, 1));
			buf += 2;
		}
		else if (dollar_idx != -1)
		{
			token_push_back(&token, get_var(buf));
			buf += get_var_len(buf) + 1;
			dollar_idx = -1;
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
