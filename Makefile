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
		lights \
		matrix} \
		}}
DEPS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.d}}
OBJS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}

MAIN_SRC = srcs/main.c
MAIN_DEPS = objs/main.d
MAIN_OBJ = objs/main.o

#COMPILING
CC = clang
CFLAGS = -Wall -Wextra -Werror -fenable-matrix -mavx -g3 -fsanitize=address
LD_FLAGS = -L ${LIBFT_DIR} -L ${MLX_DIR}
LN_FLAGS = -lmlx -lXext -lX11 -lm -lft
INCLUDES = -I ${INC_DIR} -I ${LIBFT_INC_DIR} -I ${MLX_DIR}
RM = rm -rf

################################################################################
#                                MAIN RULES								       #
################################################################################
all: ${NAME}

${NAME}: libftcreat ${OBJS} ${MAIN_OBJ}
	@make -C ${MLX_DIR} --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} ${MAIN_OBJ} -o ${NAME} ${LD_FLAGS} ${LN_FLAGS}

-include ${DEPS}
-include ${MAIN_DEPS}

libftcreat:
	@make -C ${LIBFT_DIR} --no-print-directory

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${dir $@}
	@echo create: ${@:%=%}
	@${CC} ${CFLAGS} -MMD ${INCLUDES} -o $@ -c $<

main.o: main.c
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

CR_DIR = ~/Criterion
CR_INC_DIR = ${CR_DIR}/include/criterion
CR_INCLUDES = -I ${CR_INC_DIR}
LD_CR_FLAGS = -L ${CR_DIR}/build/src
LN_CR_FLAGS = -lcriterion

TEST_DIR = sandbox
TEST_NAME = lights
TEST_FILE = ${SRC_DIR}/chap6_lights
TEST_SRC = ${TEST_FILE}.c
TEST_DEPS = ${TEST_FILE}.d
TEST_OBJ = ${TEST_FILE}.o
TEST_INC = ${CR_INCLUDES} ${INCLUDES}
TEST_LDFLAGS = ${LD_CR_FLAGS} ${LD_FLAGS}
TEST_LNFLAGS = ${LN_CR_FLAGS} ${LN_FLAGS}

test: libftcreat ${OBJS} ${TEST_OBJ}
	@make -C ${MLX_DIR} --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} ${TEST_OBJ} -o ${TEST_NAME} ${TEST_LDFLAGS} ${TEST_LNFLAGS}
	@./${TEST_NAME}
	@${RM} {TEST_NAME} ${TEST_DEPS} ${TEST_OBJ}

-include ${DEPS}
-include ${TEST_DEPS}

${TEST_FILE}.o: ${TEST_FILE}.c
	@${CC} ${CFLAGS} ${TEST_INC} -I includes -MMD -o $@ -c $<

testlittleclean: littleclean
	@${RM} ${TEST_NAME}
	@echo "deleted test program"

testr: testlittleclean test

.PHONY: all clean fclean re libftcreat val norm littleclean r test testlittleclean testr
