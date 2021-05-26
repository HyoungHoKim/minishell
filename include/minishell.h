#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "term.h"

# define MAXSIZE	1024
# define SUCCESS	0
# define FAILURE	1

# define SEMI		0
# define PIPE		1
# define REOUT		2
# define REIN		3

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

typedef struct		s_parse
{
	char			*input;
	char			*buf;
	char			quote;
}					t_parse;

typedef struct		s_state
{
	int				my_errno;
	char			**env;
	t_hist			*hist;
	struct termios	backup;
}					t_state;

extern t_state		g_state;

void				show_prompt();
char				**copy_envp(char **envp);
void				handle_signal(int signo);

void				free_hist(t_hist *hist);
void				hist_pop_front(t_hist **head);
void				hist_push_front(t_hist **head, char *line);
void				print_prev_hist(t_hist **hist, t_input *input);
void				print_next_hist(t_hist **hist, t_input *input);

int					get_line(char **line);
int					get_chr_pos(char *line, char c);
void				print_cmd_token(t_cmd *cmd);

int					parser(char *line, t_cmd *cmd);
int					tokenizer(t_parse *parse, t_cmd *cmd);
int					get_flag(char c);

char				**create_token(void);
int					token_size(char **token);
int					token_push_back(char ***token, char *str);
void				free_token(char **token);
char				*join_token(char **token);

t_cmd				*create_cmd(void);
t_cmd				*add_cmd(t_cmd *cur);
t_cmd				*rewind_cmd(t_cmd *cmd);
void				free_cmd(t_cmd *cmd);
int					cmd_size(t_cmd *cmd);

char				*get_env(char *key);
int					get_env_idx(char *key);
char				*get_env_key(char *env);
char				*get_env_value(char *key);
void				print_env(void);
int					check_invalid_key(char *key);

char				*expand_var(char *buf);
int					get_split_idx(char *buf, int *bs_idx, int *dr_idx);
int					is_set(char c, char *set);

void				print_sort_env(void);
char				*add_back_slash(char *value);

void				ft_echo(char **token);
void				ft_pwd(void);
void				ft_env(char **token);
void				ft_cd(char **token);
void				ft_export(char **token);
void				ft_unset(char **token);
void				ft_exit(char **token);

void				exec_command(t_cmd *cmd);
void				exec_builtin(char **token);
int					check_builtin(char **token);
char				*find_extern_dir(char *token);
int					exec_pipe(t_cmd *cmd);

int					err_msg(char *command, char *err_type, char *comment, int my_errno);
int					err_msg_export(char *command, char *err_type, char *comment, int my_errno);
int					err_msg_extern(char *err_type, char *comment);

#endif
