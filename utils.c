#include "minishell.h"

int             get_chr_pos(char *line, char c)
{
    int         idx;

    idx = 0;
    while (line[idx] != '\0')
    {
        if (line[idx] == c)
            return (idx);
        idx++;
    }
    return (idx);
}

void			show_prompt()
{
    static char	*path;

    path = getcwd(path, MAXSIZE);
    ft_putstr_fd(path, STDIN);
    ft_putstr_fd("$ ", STDIN);
}

char		*del_side_space(char *line)
{
	int		st;
	int		ed;
	char	*ret;

    if (!line)
        return (0);
	st = 0;
	ed = ft_strlen(line) - 1;
	while (line[st] == ' ')
		st++;
	while (line[ed] == ' ')
		ed--;
	ret = (char*)malloc(sizeof(char) * (ed - st + 2));
	ft_strlcpy(ret, line + st, (ed - st + 2));
	free(line);
	return (ret);
}