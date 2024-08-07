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

NAME = fdf

LIBFT = libft
MLX = minilibx-linux

LIBFT_A = $(LIBFT)/libft.a
MLX_A = $(MLX)/libmlx.a

INCLUDES = -I$(MLX) -I. -I$(LIBFT)

CC = cc
FLAGS = -Werror -Wextra -Wall $(INCLUDES)
LDFLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm

SRC = new_fdf.c error_handling.c parse.c parse_utils.c draw.c parse_color.c parse_color_utils.c
OBJS = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	@$(CC) $(FLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT)

$(MLX_A):
	@$(MAKE) -s -C $(MLX)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re