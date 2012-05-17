SRC = helloworld.cpp
OBJ = ${SRC:.cpp=.o}
EXE = hello
CC = g++
 
all:
	$(CC) $(OBJ) -o $(EXE)
	
helloworld.o: helloworld.cpp
	$(CC) $(SRC) -o $(OBJ) 
clean:
	rm $(OBJ)

help:
	echo -e Available targets: all, clean, helloworld.o
