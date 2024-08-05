NAME = fdf

LIBFT_A = libft/libft.a
MLX_A = mlx/libmlx.a

LIBFT = libft/
MLX = mlx/

INCLUDES = -Imlx -I. -Ilibft

CC = cc
FLAGS = -Werror -Wextra -Wall $(INCLUDE)
LDFLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm

SRC = new_fdf.c error_handling.c parse.c parse_utils.c draw.c parse_color.c parse_color_utils.c
OBJS = $(SRC:%.c=%.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(MLX_A)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_A):
	@$(MAKE) -s -C $(LIBFT)

$(MLX_A):
	@$(MAKE) -s -C $(MLX)

clean:
	RM $(OBJS)

fclean: clean
	RM $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re