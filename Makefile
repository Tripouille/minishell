NAME				= minishell

INCLUDES			= includes/minishell.h libft/libft.h
SRCS				= $(addprefix srcs/, main.c error.c initializer.c \
						run_command.c manage_fd.c variable.c \
						command_utils.c env.c variable_utils.c \
						executable.c parse_buffer.c ask_for_command.c \
						redirection.c signal.c escape.c split_redirections.c \
						invalid_redirection.c handle_argument.c)
SRCS				+= $(addprefix srcs/builtins/, builtin_echo.c \
						builtin_exit.c builtin_env.c builtin_export.c \
						builtin_unset.c builtin_pwd.c builtin_cd.c)

OBJS				= ${SRCS:.c=.o}

ifdef san
CFLAGS				= -g3 -Wall -Wextra -Werror -I includes/ -I libft/ -fsanitize=thread
else
CFLAGS				= -g3 -Wall -Wextra -Werror -I includes/ -I libft/
endif

all:				${NAME}

.c.o:
					gcc ${CFLAGS} -c $< -o ${<:.c=.o}

$(OBJS):			${INCLUDES}

lib:
					make -C libft/

$(NAME):			lib ${INCLUDES} ${OBJS}
					#gcc ${CFLAGS} -Llibft -lft ${OBJS} -o ${NAME}
					gcc ${CFLAGS} ${OBJS} -Llibft -lft -o ${NAME}

bonus:				all

clean:
					make fclean -C libft/
					rm -rf ${OBJS}

fclean:				clean
					rm -rf ${NAME}

re:					fclean all

.PHONY:				all lib bonus clean fclean re
