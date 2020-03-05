NAME				= minishell

INCLUDES			= $(addprefix includes/, minishell.h libft.h)
SRCS				= $(addprefix srcs/, main.c error.c initializer.c \
						command.c parse_command.c shell_variable.c \
						command_utils.c)
SRCS				+= $(addprefix srcs/builtins/, builtin_echo.c \
						builtin_exit.c builtin_env.c builtin_export.c \
						builtin_unset.c builtin_pwd.c builtin_cd.c)

OBJS				= ${SRCS:.c=.o}

CFLAGS				= -g3 -Wall -Wextra -Werror -I includes -fsanitize=address

test:				all
					./${NAME}

all:				${NAME}

.c.o:
					gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(OBJS):			${INCLUDES}

lib:
					make -C libft/

$(NAME):			lib ${INCLUDES} ${OBJS}
					gcc ${CFLAGS} -Llibft -lft ${OBJS} -o ${NAME}

bonus:				all

clean:
					make fclean -C libft/
					rm -rf ${OBJS}

fclean:				clean
					rm -rf ${NAME}

re:					fclean all

.PHONY:				all lib bonus clean fclean re
