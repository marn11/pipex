NAME = pipex

NAME_BONUS = pipex_bonus

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address

RM		= rm -rf

SRCS	= src/pipex.c \
		  src/pipexutils.c \

SRCS_BONUS	= bonus_src/pipex_bonus.c \
			  bonus_src/utils_bonus.c \
			  bonus_src/utils2_bonus.c \

OBJS	= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all:	$(NAME)

bonus: $(NAME_BONUS)

%_bonus.o : bonus_src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c pipex.h 
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME):	$(OBJS) 
			make -C utilities
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) utilities/utils.a

$(NAME_BONUS): $(OBJS_BONUS) 
			   make -C bonus_utilities
			   $(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) bonus_utilities/utils.a

clean:
			$(RM) $(OBJS) $(OBJS_BONUS)
			make clean -C utilities
			make fclean -C bonus_utilities

fclean:		clean
			$(RM) $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY : clean fclean re all
