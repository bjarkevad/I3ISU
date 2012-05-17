CC = g++
SRC = *.cpp
EXE = PLCS



all:
	$(CC) -g -O0 -lpthread -D_REENTRANT -o $(EXE) $(SRC) -DBOOST_SUPPORT 
run:
	./$(EXE)
