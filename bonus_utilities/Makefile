NAME	= utils.a

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

SRCS	= ft_split2.c get_next_line2.c pipex_utils2.c utils2.c ft_splitt.c

OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

%.o : %.c utilities2.h get_next_line2.h
	cc ${CFLAGS} -c $< -o $@

$(NAME):	$(OBJS)
			ar rc $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		clean fclean re all
