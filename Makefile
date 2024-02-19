NAME = pipex

NAME_BONUS = pipex_bonus

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

SRCS	= src/pipex.c \
		  src/pipexutils.c \
		  utilities/ft_split.c \
		  utilities/ft_split1.c \
		  utilities/pipex_utils.c \
		  utilities/utils.c \

SRCS_BONUS	= bonus_src/pipex_bonus.c \
			  bonus_src/utils_bonus.c \
			  bonus_src/utils2_bonus.c \
			  bonus_src/utils3_bonus.c \
			  bonus_src/utils4_bonus.c \
			  bonus_utilities/ft_split2.c \
			  bonus_utilities/ft_splitt.c \
			  bonus_utilities/get_next_line2.c \
			  bonus_utilities/pipex_utils2.c \
			  bonus_utilities/utils2.c \


OBJS	= $(SRCS:.c=.o)


OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

all:	$(NAME)

bonus: $(NAME_BONUS)

%_bonus.o : bonus_src/%.c bonus_utilities/%.c  bonus_src/%.h bonus_utilities/%.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c src/pipex.h utilities/utilities.h
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME):	$(OBJS) 
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(NAME_BONUS): $(OBJS_BONUS) 
			   $(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

$(OBJS_BONUS): bonus_src/pipex_bonus.h bonus_utilities/get_next_line2.h bonus_utilities/utilities2.h
clean:
			$(RM) $(OBJS) $(OBJS_BONUS)

fclean:		clean
			$(RM) $(NAME) $(NAME_BONUS)

re:			fclean all

.PHONY : clean fclean re all
