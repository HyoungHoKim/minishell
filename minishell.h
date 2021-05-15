#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>

#define	STDIN		0
#define MAXSIZE		1024

typedef struct		s_hist
{
	char			*line;

	struct s_hist	*prev;
	struct s_hist	*next;
}					t_hist;

typedef struct		s_cmd
{
	char			**token;
	int				flag;

	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

extern int			g_exit;

void				show_prompt();
char				**copy_envp(char **envs);
void				handle_signal(int signo);

int					get_line(char **line);
int					get_chr_pos(char *line, char c);

void                cline_print(t_cline *head);
char				*del_side_space(char *com_line);

char				**tokenizer(char *line);

#endif
