NAME	= minishell

SRCS	= main.c utils_env.c utils_sig.c utils.c get_line.c \
		  parser.c tokenizer.c token_util.c cmd_util.c expand_var.c \
		  parser_util.c expand_var_util.c \
		  termcap.c handle_keycode.c \
		  exec_command.c ft_echo.c ft_pwd.c ft_env.c ft_cd.c \
		  ft_export.c ft_unset.c ft_exit.c extern_func.c
OBJS	= $(SRCS:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
SANITIZE	= -fsanitize=address

LIBFT	= libft.a
LIBS	= -L./libft -lft
LIBS	+= -ltermcap


all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(LIBS) $(SANITIZE) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) -g -o $@ -c $<

clean:
	$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re: fclean all
