#***************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbisko <dbisko@student.42berlin.de>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 15:13:25 by dbisko            #+#    #+#              #
#    Updated: 2024/08/07 11:47:44 by dbisko           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c \
       ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
       ft_strrchr.c ft_strncmp.c ft_strnstr.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
       ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c ft_printf.c ft_print_str.c \
       ft_print_pnt.c ft_print_number.c ft_hex.c
B_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(B_OBJS)
	ar rcs $(NAME) $(OBJS) $(B_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
