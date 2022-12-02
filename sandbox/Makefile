################################################################################
#                                VARIABLES									   #
################################################################################

#PROGRAM
NAME = test

#LIBRAIRIES
LIBFT_DIR = ../libft
MLX_DIR = ../mlx

#FILES
INC_DIR = ../includes
LIBFT_INC_DIR = ${LIBFT_DIR}/includes
OBJS = ../objs/${wildcard *.o}

TEST_SRCS = sandbox/chap6_lights.c
TEST_OBJS = ${TEST_SRCS:.c.o}

#COMPILING
CC = clang
CFLAGS = -Wall -Wextra -Werror -fenable-matrix -mavx -g3 -fsanitize=address
LD_FLAGS = -L ${LIBFT_DIR} -L ${MLX_DIR}
LIBS_FLAGS = -lmlx -lXext -lX11 -lm -lft
INCLUDES = -I ${INC_DIR} -I ${LIBFT_INC_DIR} -I ${MLX_DIR}
RM = rm -rf

################################################################################
#                                MAIN RULES								       #
################################################################################
all: ${NAME}

${NAME}: libftcreat ${OBJS}
	@make -C ${MLX_DIR} --no-print-directory
	@make -C ..
	@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} ${TEST_OBJ} -o ${NAME} ${LIBS_FLAGS}

-include ${DEPS}

libftcreat:
	@make -C ${LIBFT_DIR} --no-print-directory

.c.o:
	@mkdir -p ${dir $@}
	@echo create: ${@:%=%}
	@${CC} ${CFLAGS} -MMD ${INCLUDES} -o $@ -c $<

################################################################################
#                              ADDITIONAL RULES								   #
################################################################################

val: ${NAME}
	valgrind ./${NAME}

norm: ${NAME}
	norminette ${SRCS} ${INC_DIR} ${LIBFT_DIR}/${SRCS} ${LIBFT_DIR}/${INC_DIR}

clean:
	@make clean -C ${LIBFT_DIR} --no-print-directory
	@make clean -C ${MLX_DIR} --no-print-directory
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C ${LIBFT_DIR} --no-print-directory
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