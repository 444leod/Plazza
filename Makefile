##
## EPITECH PROJECT, 2024
## Plazza
## File description:
## Makefile
##

NAME = plazza

SRC =	src/main.cpp \
		src/Setup.cpp \
		src/Runner.cpp \
		src/Kitchen.cpp \
		src/Reception.cpp \
		src/ThreadPool.cpp \
		src/IPC/Packet.cpp \
		src/IPC/NamedPipes.cpp \
		src/IPC/IpcTool.cpp \
		src/Pizzas/IPizzaFactory.cpp \
		src/Pizzas/Ingredients.cpp \
		src/lib/Fork.cpp \
		src/lib/FileDescriptorMonitor.cpp \

OBJ = $(SRC:.cpp=.o)

CC = g++

CXXFLAGS	+=	-Wall -Wextra -Werror -Wpedantic -std=c++20
CXXFLAGS 	+=	-I./include -I./src -I./src/Pizzas -I./src/IPC -I./src/lib

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: all

run: all

init: install-hooks install-mango

install-hooks:
	@cp .githooks/commit-msg .git/hooks/commit-msg
	@chmod +x .git/hooks/commit-msg
	@echo "Hooks installed."

install-mango:
	@chmod +x ./init/install-mango.sh
	@./init/install-mango.sh

.PHONY: all clean fclean re
.SILENT: run
