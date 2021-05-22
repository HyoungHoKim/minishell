# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyoukim <hyoukim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 22:08:16 by hyoukim           #+#    #+#              #
#    Updated: 2021/05/22 17:02:38 by hari3o           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		= 	-Wall -Werror -Wextra
NAME		=	libft.a
SRCS		=	ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isprint.c ft_putchar_fd.c ft_putnbr_fd.c \
				ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c \
				ft_strncmp.c ft_strlcat.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
				ft_memmove.c ft_memchr.c ft_memcmp.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
				ft_isalnum.c ft_isascii.c ft_toupper.c ft_tolower.c ft_calloc.c ft_substr.c \
				ft_strtrim.c ft_itoa.c ft_strmapi.c ft_putendl_fd.c ft_strcmp.c \
				ft_putchar.c ft_numlen.c
SRCS_B		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c
D_OBJS		=	obj
OBJS 		= 	$(addprefix $(D_OBJS)/, $(SRCS:.c=.o))
OBJS_B		=	$(addprefix $(D_OBJS)/, $(SRCS_B:.c=.o))

all: $(NAME)

$(NAME): $(D_OBJS) $(OBJS) $(OBJS_B)
	ar rcs $(NAME) $(OBJS) $(OBJS_B)

$(D_OBJS):
	mkdir -p $(D_OBJS)

$(D_OBJS)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(D_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
