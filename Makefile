INC_DIR = includes/
SRC_DIR = srcs/
OBJ_DIR = objs/
MLX_DIR = minilibx/
LIBFT_DIR = libft/

SRCS = mlx_window.c
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

NAME = test

CFLAGS = -Werror -Wextra -Wall -g -fsanitize=address
LINKS = -lmlx -lm -lft -g -fsanitize=address
INCPATH = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)includes/
LIBPATH = -L$(MLX_DIR) -L$(LIBFT_DIR)

MLX = $(MLX_DIR)/libmlx.a
LIBFT = $(LIBFT_DIR)libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS)
	gcc $(OBJS) $(LIBPATH) $(LINKS) -framework OpenGL -framework AppKit -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) $(INCPATH) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Iminilibx -O3  -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

bonus: all

re: fclean all

.PHONY: all clean fclean re mlx libft