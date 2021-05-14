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

char		*del_side_space(char *com_line)
{
	int		st;
	int		ed;
	char	*ret;

	st = 0;
	ed = ft_strlen(com_line) - 1;
	while (com_line[st] == ' ')
		st++;
	while (com_line[ed] == ' ' || com_line[ed] == '\n')
		ed--;
	ret = (char*)malloc(sizeof(char) * (ed - st + 2));
	ft_strlcpy(ret, com_line + st, (ed - st + 2));
	free(com_line);
	return (ret);
}