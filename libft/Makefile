NAME				= libft.a
INCLUDE				= libft.h
SRCS				= $(addprefix srcs/, slen.c ft_isdigit.c ft_strncmp.c \
					ft_strlcpy.c ft_strlcat.c cinstr.c skip_spaces.c \
					ft_atoi.c ft_calloc.c ft_strdup.c square.c ft_strcmp.c \
					ft_strndup.c ft_split.c ft_strjoin.c str_array_size.c \
					free_str_array.c ft_itoa.c ft_itoa_copy.c)
OBJS				= ${SRCS:.c=.o}
CFLAGS				= -Wall -Wextra -Werror -I .

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
