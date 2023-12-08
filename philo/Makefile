########################################
########## VARIABLES

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -f

########################################
########## COLORS
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

########################################
########## SOURCES
SRCS	=	main.c utils.c parsing.c

OBJS	=	$(SRCS:.c=.o)

.c.o:
		@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
		@echo "$(MAGENTA)Compilation of : $<..$(DEF_COLOR)"

########################################
########## RULES

all:		$(NAME)

$(NAME):	$(OBJS)
				@$(CC) $(OBJS) -o $(NAME)
				@echo "$(GREEN)Success compilation of $(NAME) !$(DEF_COLOR)"

clean:
				@$(RM) $(OBJS)
				@echo "$(YELLOW)rm of $(OBJS).$(DEF_COLOR)"

fclean: 	clean
				@$(RM) $(NAME)
				@echo "$(RED)rm of $(NAME).$(DEF_COLOR)"



re:			fclean all

norm:
			norminette $(SRCS) | grep -v Norme -B1 || true

.PHONY: all clean fclean re norm
