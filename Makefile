CC = @gcc
CFLAGS = -Wall -Wextra -pedantic-errors

SRC = useful/builtin.c image_system/color_system.c image_system/image_system.c main.c NeuralNetworks/BuiltinsNeuralNetworks.c NeuralNetworks/NeuralNetwork.c 

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
	@rm -f $(OBJ)
	@rm -f a.out
	@echo "Cleared"

