#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>

#define	STDIN		0
#define MAXSIZE		1024

typedef struct		s_cline
{
	char			flag;
	char			*com_line;
	char			**token;
	struct	s_cline *next;
}					t_cline;

extern char         **g_envp;

void				show_prompt();
char				**copy_envp(char **envs);
void				handle_signal(int signo);
int					get_line(char **line);
int					get_chr_pos(char *line, char c);
void				parser(t_cline **head, char *line);
t_cline		        *cline_new(char *com_line, char flag);
void				cline_add_back(t_cline **lst, t_cline *new);
void                cline_print(t_cline *head);
char				*del_side_space(char *com_line);
void				tokenizer(t_cline **head);


#endif
