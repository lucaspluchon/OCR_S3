CC = @gcc
CFLAGS = -Wall -Wextra -pedantic-errors

SRC = builtin.c color_system.c image_system.c main.c

LINKERFLAGS = -lSDL2main -lSDL2 -lSDL2_image

OBJ= $(SRC:.c=.o)

all: compile exec

compile: $(OBJ)
	@echo "Compiled"

exec:
	@gcc $(OBJ) $(CFLAGS) $(LINKERFLAGS)
	@echo "a.out generated"

clear :
	@rm -f *.o
	@rm -f a.out
	@echo "Cleared"

	
list :
	@echo "All c files"
	@echo *.c
