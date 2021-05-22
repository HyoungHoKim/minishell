NAME	= minishell

D_LIBFT	= libft
D_OBJS	= obj

LIBFT	= $(D_LIBFT)/libft.a

SRCS	= main.c \
		  utils_env.c \
		  utils_sig.c \
		  utils.c \
		  get_line.c \
		  parser.c \
		  tokenizer.c \
		  token_util.c \
		  cmd_util.c \
		  expand_var.c \
		  parser_util.c \
		  expand_var_util.c \
		  termcap.c \
		  handle_keycode.c \
		  history.c \
		  exec_command.c \
		  ft_echo.c \
		  ft_pwd.c \
		  ft_env.c \
		  ft_cd.c \
		  ft_export.c \
		  ft_unset.c \
		  ft_exit.c \
		  extern_func.c
OBJS	= $(addprefix $(D_OBJS)/, $(SRCS:.c=.o))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
SANITIZE	= -fsanitize=address -g
CFLAGS		+= $(SANITIZE)
RM			= rm -rf

INC		= -I$(D_LIBFT)

LIBS	= -L$(D_LIBFT)/
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

$(D_OBJS)/%.o: %.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	$(MAKE) -C $(D_LIBFT) clean
	$(RM) $(D_OBJS)

fclean: clean
	$(MAKE) -C $(D_LIBFT) fclean
	$(RM) $(NAME)

re: fclean all
