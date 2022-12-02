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
INIT_DIR = setup
UTILS_DIR = utils
SRCS = ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
		main \
		error \
		exit_clear \
		display \
		drawscene \
		${addprefix ${INIT_DIR}/, \
		setup_scene \
		parse_file \
		set_params \
		conv_to_tuple \
		conv_to_float \
		elem_add} \
		${addprefix ${UTILS_DIR}/, \
		tuple \
		ray \
		rayutils \
		interlst \
		matrix} \
		}}
DEPS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.d}}
OBJS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}

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
	@${CC} ${CFLAGS} ${LD_FLAGS} ${OBJS} -o ${NAME} ${LIBS_FLAGS}

-include ${DEPS}

libftcreat:
	@make -C ${LIBFT_DIR} --no-print-directory

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

################################################################################
#                              		TESTS							   		   #
################################################################################

CRITERION_DIR = /mnt/nfs/homes/rokerjea/sgoinfre/Criterion/

test: libftcreat
	clear
	@${CC} -o matrix srcs/utils/matrix.c sandbox/chap3_matrix.c ${INCLUDES} -I${CRITERION_DIR}include -L${CRITERION_DIR}build/src ${CFLAGS} -lm -lcriterion
	@./matrix
	@rm matrix

test2: libftcreat
	clear
	@${CC} -o ray srcs/utils/ray.c srcs/utils/interlst.c libft/libft.a srcs/utils/tuple.c srcs/utils/matrix.c srcs/utils/rayutils.c sandbox/chap5_sphere_tests.c ${INCLUDES} -I${CRITERION_DIR}include -L${CRITERION_DIR}build/src ${CFLAGS} -lm -lcriterion
	@./ray
	@rm ray

TEST3_SRC = ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
		error \
		exit_clear \
		display \
		${addprefix ${INIT_DIR}/, \
		setup_scene \
		parse_file \
		set_params \
		conv_to_tuple \
		conv_to_float \
		elem_add} \
		${addprefix ${UTILS_DIR}/, \
		tuple \
		ray \
		rayutils \
		interlst \
		matrix} \
		}\
		sandbox/chap7_scene}

test3:	libftcreat
	clear
	@${CC} -o world ${TEST3_SRC} ${LD_FLAGS} ${INCLUDES} -I${CRITERION_DIR}include -L${CRITERION_DIR}build/src ${CFLAGS} -lcriterion ${LIBS_FLAGS}
	@./world
	@rm world

.PHONY: all clean fclean re libftcreat val norm littleclean r
