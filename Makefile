NAME	:= minishell

D_LIBFT	:= libft
D_OBJS	:= obj
D_SRCS	:= src
D_INC	:= include

LIBFT	:= $(D_LIBFT)/libft.a

SRC		:= main.c \
		  utils_env.c \
		  utils_sig.c \
		  utils.c \
		  get_line.c \
		  parser.c \
		  tokenizer.c \
		  token_util.c \
		  join_token.c \
		  cmd_util.c \
		  expand_var.c \
		  parser_util.c \
		  expand_var_util.c \
		  termcap.c \
		  handle_keycode.c \
		  history.c \
		  err_msg.c \
		  ft_echo.c \
		  ft_pwd.c \
		  ft_env.c \
		  ft_cd.c \
		  ft_export.c \
		  ft_unset.c \
		  ft_exit.c \
		  exec_command.c \
		  exec_builtin.c \
		  exec_pipe.c
SRCS	:= $(addprefix, $(D_SRCS)/, $(SRC))
OBJS	:= $(addprefix $(D_OBJS)/, $(SRC:.c=.o))

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra
SANITIZE	:= -fsanitize=address -g
CFLAGS		+= $(SANITIZE)
RM			:= rm -rf

INC		:= -I$(D_LIBFT)/
INC		+= -I$(D_INC)/

LIBS	:= -L$(D_LIBFT)/
LIBS	+= -lft
LIBS	+= -ltermcap

.PHONY: all clean fclean re

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(D_LIBFT)

$(NAME): $(LIBFT) $(D_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(D_OBJS):
	mkdir -p $(D_OBJS)

$(D_OBJS)/%.o: $(D_SRCS)/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	$(MAKE) -C $(D_LIBFT) clean
	$(RM) $(D_OBJS)

fclean: clean
	$(MAKE) -C $(D_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all
