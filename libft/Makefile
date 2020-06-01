NAME				= libft.a
CFLAGS				= -Wall -Wextra -Werror -I base -I ft_printf

INCLUDE_BASE		= base/base.h
SRCS_BASE			= $(addprefix base/, cinstr.c free_str_array.c ft_atoi.c \
					ft_calloc.c ft_isdigit.c ft_itoa.c ft_itoa_copy.c ft_split.c ft_strcmp.c \
					ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
					ft_strndup.c skip_spaces.c square.c str_array_size.c ft_strccmp.c \
					ft_isalpha.c ft_isalphanum.c ft_strccpy.c ft_isspace.c)
SRCS_BASE			+= $(addprefix base/, ft_lst_addback.c ft_lst_addfront.c ft_lst_iter.c \
					ft_lst_last.c ft_lst_new.c ft_lst_purge.c ft_lst_size.c ft_lst_remove.c)
OBJS_BASE			= ${SRCS_BASE:.c=.o}

INCLUDE_GNL			= gnl/get_next_line.h
SRCS_GNL			= $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
OBJS_GNL			= ${SRCS_GNL:.c=.o}

INCLUDE_PRINTF		= ft_printf/ft_printf.h base/base.h
SRCS_PRINTF			= $(addprefix ft_printf/, ft_printf.c convertarg.c dict.c get_basics.c \
					get_numbers.c list.c utils.c utils_numbers.c \
					utils_str.c fill_buffer.c \
					get_bonus.c utils_bonus.c set_bonus.c unicode.c \
					unicode2.c fill_buffer_bonus.c getarg.c selfbonus.c macro.c)
OBJS_PRINTF			= ${SRCS_PRINTF:.c=.o}

INCLUDE_DPRINTF		= ft_dprintf/ft_dprintf.h ft_printf/ft_printf.h base/base.h
SRCS_DPRINTF		= ft_dprintf/ft_dprintf.c
OBJS_DPRINTF		= ${SRCS_DPRINTF:.c=.o}

all:				${NAME}
${OBJS_BASE}:		${INCLUDE_BASE}
${OBJS_GNL}:		${INCLUDE_GNL}
${OBJS_PRINTF}:		${INCLUDE_PRINTF}
${OBJS_DPRINTF}:	${INCLUDE_DPRINTF}

${NAME}:			${OBJS_BASE} ${OBJS_GNL} ${OBJS_PRINTF} ${OBJS_DPRINTF}
					ar -rcs ${NAME} ${OBJS_BASE} ${OBJS_GNL} ${OBJS_PRINTF} ${OBJS_DPRINTF}

.c.o:
					gcc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
					rm -rf ${OBJS_BASE} ${OBJS_GNL} ${OBJS_PRINTF} ${OBJS_DPRINTF}

fclean:				clean
					rm -rf ${NAME}

re:					fclean all

.PHONY:				all clean fclean re
