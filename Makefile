NAME				= minishell

INCLUDES			= $(addprefix includes/, minishell.h libft.h)
SRCS				= $(addprefix srcs/, main.c)

OBJS				= ${SRCS:.c=.o}

CFLAGS				= -g3 -Wall -Wextra -Werror -I includes

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
