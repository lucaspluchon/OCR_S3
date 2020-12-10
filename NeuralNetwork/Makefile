CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic-errors -std=c99 -g -ldl -lm 

SRC = NeuralNetworkOCR.c NeuralNetworkTools.c
OBJ = $(SRC:.c=.o)


all : $(OBJ)
	$(CC) $(OBJ) $(CFLAGS)

clean :
	rm -f $(OBJ)
	rm -f *.out