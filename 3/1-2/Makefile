SRC = helloworld.cpp
OBJ = ${SRC:.cpp=.o}
EXE = hello
CC = g++
 
all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
	
helloworld.o: helloworld.cpp
	$(CC) -c $(SRC)  
clean:
	rm $(OBJ)

help:
	echo -e Available targets: all, clean, helloworld.o
