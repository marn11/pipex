NAME = pipex

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

SRCS	= src/pipex.c \
		  src/pipexutils.c \


OBJS	= $(SRCS:.c=.o)

all:	$(NAME)

%.o: %.c pipex.h 
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME):	$(OBJS)
			make -C utilities
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) utilities/utils.a

clean:
			$(RM) $(OBJS)
			make clean -C utilities

fclean:		clean
			$(RM) $(NAME)
			make fclean -C utilities

re:			fclean all

.PHONY : clean fclean re all



# add bonus rule later