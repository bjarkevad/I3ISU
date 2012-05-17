CC = g++
SRC = *.cpp
EXE = PCLS
LIBS = /home/bjarke/skole/ISU/Exercises/9/osapi-src/lib/host/debug/libOSApi.a
OS = OS_LINUX
INC = /home/bjarke/skole/ISU/Exercises/9/osapi-src/inc

all:
	$(CC) -g $(SRC) -o $(EXE) $(LIBS) -I$(INC) -D$(OS) -lpthread -lrt 
