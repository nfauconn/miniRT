################################################################################
#                                VARIABLES									   #
################################################################################

#PROGRAM
NAME = miniRT

#LIBRAIRIES
LIBFT_DIR = libft
LIBFT = libft/libft.a
MLX_DIR = ./mlx

#DIRECTORIES
SRC_DIR  = ./srcs
BUILD_DIR  = ./objs
INC_DIR = ./includes
LIBFT_INC_DIR = ./libft/includes
INIT_DIR = init
PARSING_DIR = parsing
SETTING_DIR = setting
DRAW_DIR = draw
UTILS_DIR = utils

#SOURCES
S_EXT = .c
SRC_FILES = render.c \
			display.c \
			parse_input.c \
			apply_input.c \
			error.c \
			exit_clear.c \
\
				${addprefix ${INIT_DIR}/, \
					setup_scene.c \
\
						${addprefix ${PARSING_DIR}/, \
							parse_file.c \
							conv_to_tuple.c \
							conv_to_float.c \
							elem_add.c \
						} \
\
						${addprefix ${SETTING_DIR}/, \
							camera.c \
							ambiantlight.c \
							lightsource.c \
							sphere.c \
							cylinder.c \
							plane.c \
							object_params.c \
						} \
				} \
\
				${addprefix ${DRAW_DIR}/, \
					drawscene.c \
					ray.c \
					inter.c \
					inter_cy.c \
					inter_sp_pl.c \
					lights.c \
					lights_normal.c \
					scene.c \
					color.c \
				} \
\
				${addprefix ${UTILS_DIR}/, \
					tuple.c \
					tuple_create.c \
					matrix_utils.c \
					matrix_create.c \
					matrix_mult.c \
					matrix_submatrix.c \
					matrix_transform.c \
					matrix_inverse.c \
					rgb.c \
				}

SRCS = ${addprefix ${SRC_DIR}/, ${SRC_FILES}}
DEPS = ${subst ${SRC_DIR}/, ${BUILD_DIR}/, ${SRCS:%.c=%.d}}
OBJS = ${subst ${SRC_DIR}/, ${BUILD_DIR}/, ${SRCS:%.c=%.o}}

MAIN_SRC = srcs/main.c
MAIN_DEPS = objs/main.d
MAIN_OBJ = objs/main.o

#COMPILING
CC = clang
CFLAGS = -Wall -Wextra -Werror -fenable-matrix -mavx -g3 #-fsanitize=address
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

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
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

fclean: clean testfclean
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

T_INCLUDES = ${CR_INCLUDES} ${INCLUDES}
T_LDFLAGS = ${LD_CR_FLAGS} ${LD_FLAGS}
T_LNFLAGS = ${LN_CR_FLAGS} ${LN_FLAGS}

T_SRC_DIR = ${SRC_DIR}/tests
T_BUILD_DIR = ${BUILD_DIR}/tests

T_NAME = all_tests
T_SRCS = ${addsuffix ${S_EXT}, ${addprefix ${T_SRC_DIR}/, \
	tests_utils \
	chap2_color \
	chap3_matrix \
	chap5_sphere_tests \
	chap6_lights \
	chap7_scene \
	chap8_shadows \
	chap9_plane \
	}}
T_DEPS = ${subst ${T_SRC_DIR}, ${T_BUILD_DIR}, ${T_SRCS:%.c=%.d}}
T_OBJS = ${subst ${T_SRC_DIR}, ${T_BUILD_DIR}, ${T_SRCS:%.c=%.o}}
T_VPATH = ${T_SRC_DIR}

tests: libftcreat ${OBJS} ${T_OBJS}
	@make -C ${MLX_DIR} --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} ${T_OBJS} -o ${T_NAME} ${T_LDFLAGS} ${T_LNFLAGS}
	@./${T_NAME}

-include ${DEPS}
-include ${TEST_DEPS}

${TEST_FILE}.o: ${TEST_FILE}.c
	@${CC} ${CFLAGS} ${T_INCLUDES} -I includes -MMD -o $@ -c $<

testfclean: littleclean
	@${RM} ${T_NAME}
	@${RM} ${T_BUILD_DIR}
	@${RM} ${BUILD_DIR}
	@echo "deleted test program"

testr: testfclean tests

.PHONY: all clean fclean re \
	libftcreat val norm \
	littleclean r \
	testfclean testr
