CC = @gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g -ldl -lm

SRC = useful/builtin.c image_system/image_manipulation.c image_system/color_system.c image_system/image_system.c main.c demo.c character_detection/char_detect.c NeuralNetworks/BuiltinsNeuralNetworks.c NeuralNetworks/BackPropagation.c NeuralNetworks/DemoNeuralNetwork.c NeuralNetworks/FileManagment.c NeuralNetworks/NeuralNetwork.c

LINKERFLAGS = -lSDL2main -lSDL2 -lSDL2_image

OBJ= $(SRC:.c=.o)

all: compile exec

compile: $(OBJ)
	@echo "Compiled"

exec:
	@gcc $(OBJ) $(CFLAGS) $(LINKERFLAGS)
	@echo "a.out generated"

clean :
	@rm -f *.o
	@rm -f $(OBJ)
	@rm -f a.out
	@echo "Cleaned"

