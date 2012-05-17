CC = g++
SRC = *.cpp
OBJ = $(SRC:.cpp=.o)
EXE = PLCS

all: 
	$(CC) -D_REENTRANT -lpthread -o $(EXE) $(SRC) -g -O0

run:
	./$(EXE)
