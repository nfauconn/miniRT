################################################################################
#                                VARIABLES									   #
################################################################################

#PROGRAM
NAME = miniRT

#LIBRAIRIES
LIBFT_DIR = libft
LIBFT = libft/libft.a
MLX_DIR = ./mlx

#FILES
SRC_DIR  = ./srcs
S_EXT = .c
BUILD_DIR  = ./objs
INC_DIR = ./includes
LIBFT_INC_DIR = ./libft/includes
SRCS = ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
		main \
		error \
		exit_clear \
		parse \
		paramsetter \
		display \
		setup_scene \
		sphere \
		vector_operations \
		TESTdegradetry \
		}}
DEPS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.d}}
OBJS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}

#COMPILING
CC = clang
CFLAGS = -Wall -Wextra -Werror -mavx -g3 # -fsanitize=address
LD_FLAGS = -L ${LIBFT_DIR} -L ${MLX_DIR}
MLX_FLAGS = -lm -lmlx -lXext -lX11
INCLUDES = -I ${INC_DIR} -I ${LIBFT_INC_DIR} -I ${MLX_DIR}
RM = rm -rf

################################################################################
#                                MAIN RULES								       #
################################################################################
all: ${NAME}

${NAME}: ${OBJS}
	@make -C ${LIBFT_DIR}
	@make -C ${MLX_DIR}
	@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} ${MLX_FLAGS} -lft
	@echo "${NAME} created"

-include ${DEPS}

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${dir $@}
	@echo create: ${@:%=%}
	@${CC} ${CFLAGS} -MMD ${INCLUDES} -o $@ -c $<

################################################################################
#                              ADDITIONAL RULES								   #
################################################################################

val: ${NAME}
	valgrind ./${NAME}

norm: ${NAME}
	norminette ${SRCS} ${INC_DIR} ${LIBFT_DIR}

clean:
	@make clean -C ${LIBFT_DIR}
	@make clean -C ${MLX_DIR}
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	@${RM} ${NAME}
	@echo "libs and program deleted"

gitm:
	git add .
	git commit
	git push

re: fclean all

littleclean:
	@${RM} ${BUILD_DIR}
	@${RM} ${NAME}
	@echo "deleted build dir & program (libs kept)"

r: littleclean all

.PHONY: all clean fclean re
