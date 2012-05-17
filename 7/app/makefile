CC = g++
SRC = *.cpp
OBJ = $(SRC:.cpp=.o)
EXE = PLCS
CCPREFIX = arm-angstrom-linux-gnueabi-

all: 
	$(CC) -O0 -g -D_REENTRANT -lpthread -o $(EXE) $(SRC)

