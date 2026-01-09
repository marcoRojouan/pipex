NAME		= pipex

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I ./
RM			= rm -f

SRCS		= pipex.c \
			  parsing_helper/parsing_path_finding.c \
			  parsing_helper/parsing_split.c \
			  parsing_helper/parsing_utils.c
			  

OBJS		= $(SRCS:.c=.o)

HEADER		= pipex.h

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:		%.c $(HEADER)
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re