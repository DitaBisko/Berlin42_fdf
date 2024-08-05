NAME = fdf

LIBFT_A = libft/libft.a
MLX_A = mlx/libmlx.a

LIBFT = libft/
MLX = mlx/

INCLUDE = mlx/mlx.h fdf.h libft/libft.h

CC = cc
FLAGS = -Werror -Wextra -Wall -I$(INCLUDE)

SRC = fdf.c error_handling.c pars_utils.c
OBJS = $(SRCS:%.c=%.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -lft -L$(MLX) -lmlx -lm -o $(NAME) -framework OpenGL -framework AppKit

$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT)

$(MLX_A):
	@$(MAKE) -s -C $(MLX)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re