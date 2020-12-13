CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=c99 -g 

SRC = NeuralNetworkOCR.c NeuralNetworkTools.c ForwardProp.c BackProp.c
OBJ = $(SRC:.c=.o)


all : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS)

clean :
	rm -f $(OBJ)
	rm -f *.out