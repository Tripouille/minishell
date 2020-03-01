NAME				= libft.a
INCLUDE				= libft.h
SRCS				= $(addprefix srcs/, slen.c ft_isdigit.c ft_strncmp.c \
					ft_strlcpy.c ft_strlcat.c \
					ft_atoi.c ft_calloc.c ft_strdup.c square.c ft_strcmp.c)
OBJS				= ${SRCS:.c=.o}
CFLAGS				= -Wall -Wextra -Werror

all:				${NAME}

$(OBJS):			${INCLUDE}

${NAME}:			${OBJS}
					ar -rcs ${NAME} ${OBJS}

.c.o:
					gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
					rm -rf ${OBJS}

fclean:				clean
					rm -rf ${NAME}

re:					fclean all

.PHONY:				all clean fclean re
