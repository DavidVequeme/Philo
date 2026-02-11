NAME := philo

SRC :=	philo_helpers.c \
		philo_create.c \
		philo_check.c \
		philo_actions.c \
		philosophers.c \
		parsing.c \

HDR_DIR := .

FLAGS := -Wall -Wextra -Werror 

AR := ar -rcs

RM := rm -f


COLOUR_GREEN := \033[1;32m
COLOUR_RED := \033[1;31m
COLOUR_YELLOW := \033[1;33m
COLOUR_BLUE := \033[1;34m
COLOR_WHITE := \033[0m

all: $(NAME)

$(NAME): $(SRC)
	@cc $(FLAGS) $(SRC) -o $(NAME)
	@echo "$(COLOUR_GREEN)	Making $(NAME)$(COLOUR_WHITE)"

clean:
	@$(RM) $(SRC:.c=.o)
	@echo "$(COLOUR_YELLOW)	Cleaning objects of $(NAME)$(COLOUR_WHITE)"
	@echo "$(COLOUR_YELLOW)	There are none!$(COLOUR_WHITE)"

fclean:
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED)	Cleaning $(NAME)$(COLOUR_WHITE)"

re: fclean all

.PHONY: all clean fclean re