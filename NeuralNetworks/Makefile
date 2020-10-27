CC = @gcc
CFLAGS = -Wall -Wextra -Werror -pedantic-errors -g


all :
	@gcc *.c $(CFLAGS)


neural : NeuralNetwork.o BackPropagation.o BuiltinsNeuralNetworks.o
	@gcc NeuralNetwork.o BackPropagation.o BuiltinsNeuralNetworks.o

clean :
	@rm -f *.o
	@rm -f *.out