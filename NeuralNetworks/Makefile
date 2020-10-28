CC = @gcc
CFLAGS = -Wall -Wextra -Werror -pedantic-errors -g


all :
	@gcc *.c $(CFLAGS)


neural : NeuralNetwork.o BackPropagation.o BuiltinsNeuralNetworks.o FileManagment.o DemoNeuralNetwork.o
	@gcc NeuralNetwork.o BackPropagation.o BuiltinsNeuralNetworks.o FileManagment.o DemoNeuralNetwork.o

clean :
	@rm -f *.o
	@rm -f *.out
	@rm -f value
	@rm -f bias