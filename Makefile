CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= minishell
SRCS	= main.c utils_env.c utils_sig.c utils.c get_line.c \
		  parser.c tokenizer.c token_util.c cmd_util.c expand_var.c \
		  exec_command.c ft_echo.c ft_pwd.c ft_env.c
LIBFT	= libft.a
LIBS	= -L./libft -lft

SANITIZE	= -fsanitize=address

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(LIBFT)
	$(CC) $(SANITIZE) $(SRCS) $(LIBS) -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re: fclean all 
