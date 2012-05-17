CC = g++
CFLAGS = 
EXE = parttest
OBJS = ${SRC:.cpp=.o}
SRC = part1.cpp part2.cpp main.cpp

all: $(OBJS) 
	$(CC) $(OBJS) -o $(EXE) 

main.o: part1.o part2.o main.cpp
	$(CC) -c main.cpp 

part1.o: part1.cpp part1.h
	$(CC) -c part1.cpp  

part2.o: part2.cpp part2.h
	$(CC) -c part2.cpp  

clean:
	rm -f $(OBJS)

run:
	./$(EXE)

help:
	echo -e "Available targets: all, main.o, part1.o, part2.o, clean, help."
