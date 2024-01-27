NAME	= utils.a

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

SRCS	= ft_split.c get_next_line.c pipex_utils.c utils.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

%.o : %.c utilities.h get_next_line.h
	cc ${CFLAGS} -c $< -o $@

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		clean fclean re all
