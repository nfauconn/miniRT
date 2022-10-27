SRCS		= mlx_window.c

NAME		= test

OBJS		= ${SRCS:.c=.o}

CC			= gcc

CFLAGS		= -Wall -Werror -Wextra -g

INCLUDES	= -I libft -I mlx

all:		$(NAME)

.c.o:
			${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			make re -C libft --no-print-directory
			make -C mlx --no-print-directory
			${CC} ${CFLAGS} ${OBJS} -Llibft -lft -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz ${INCLUDES} -o $(NAME)

clean:
			make clean -C libft --no-print-directory
			rm -f ${OBJS}

fclean:		clean
			make fclean -C libft --no-print-directory
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re