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
	int				fd[2];

	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_token
{
	char			*input;
	char			*buf;
	char			quote;
}					t_token;

typedef struct		s_state
{
	int				ext;
	char			**env;
}					t_state;

extern t_state		g_state;

void				show_prompt();
char				**copy_envp(char **envs);
void				handle_signal(int signo);

int					get_line(char **line);
int					get_chr_pos(char *line, char c);

int					parser(char *line, t_cmd *cmd);
char				*del_side_space(char *line);

char				**tokenizer(char *line);

#endif
