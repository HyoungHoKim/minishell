CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
NAME	= minishell
SRCS	= main.c utils_env.c utils_sig.c utils.c get_line.c \
		  parser.c tokenizer.c token_util.c cmd_util.c
LIBFT	= libft.a
LIBS	= -L./libft -lft

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(LIBFT)
	$(CC) $(SRCS) $(LIBS) -o $(NAME)

clean:
	$(MAKE) -C ./libft clean
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re: fclean all 
