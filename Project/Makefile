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
SRC_FILES =	main.c \
			display.c \
			drawscene.c \
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

${NAME}: libftcreat ${OBJS}
	@make -C ${MLX_DIR} --no-print-directory
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} ${LD_FLAGS} ${LN_FLAGS}

-include ${DEPS}

libftcreat:
	@make -C ${LIBFT_DIR} --no-print-directory

${BUILD_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${dir $@}
	@echo create: ${@:%=%}
	@${CC} ${CFLAGS} -MMD ${INCLUDES} -o $@ -c $<

################################################################################
#                              ADDITIONAL RULES								   #
################################################################################

val: ${NAME}
	valgrind ./${NAME}

norm: ${NAME}
	norminette ${SRC_DIR} ${INC_DIR} ${LIBFT_DIR}/${SRC_DIR} ${LIBFT_DIR}/${INC_DIR}

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