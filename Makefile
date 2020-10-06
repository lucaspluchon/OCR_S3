CC = gcc
CFLAGS = -lSDL2main -lSDL2 -lSDL2_image -Wall -Wextra -pedantic-errors

SRC = builtin.c color_system.c image_system.c main.c

OBJ= $(SRC:.c=.o)

all: compile exec

compile: $(OBJ)

exec:
	@gcc $(OBJ) $(CFLAGS)

clear :
	@rm -f *.o
	@rm -f a.out
	@echo "Cleared"