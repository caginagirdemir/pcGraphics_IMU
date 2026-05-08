NAME = imu
FLAGS = -Wall -Werror -Wextra

# controll codes
RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
UP			=	\033[A
CUT			=	\033[K

all:
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@c++ -o $(NAME) ./src/main.cpp ./src/Realtime.cpp -o $(NAME)
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"
