CC = g++
EXE = parttest
#Kun den første SRC.cpp fil ændres til host/SRC.cpp, burde kunne laves så det virker
#OBJS = $(SUBDIR)${SRC:.cpp=.o}
#WORKAROUND :(
OBJS = $(SUBDIR)main.o $(SUBDIR)part1.o $(SUBDIR)part2.o
SRC = part1.cpp part2.cpp main.cpp
SUBDIR = host/

#all afhænger af dir, dir laver mappen host/
all: dir $(OBJS) 	
	$(CC) $(OBJS) -o $(SUBDIR)$(EXE) 

#main.o ligger nu i $(SUBDIR)
#Det er nu nødvendigt at specificere en output fil, da undermappen ikke registreres i target navnet, og .o filen
#vil derfor ikke komme til at ligge i $(SUBDIR)
$(SUBDIR)main.o: $(SUBDIR)part1.o $(SUBDIR)part2.o main.cpp
	$(CC) -c main.cpp -o $(SUBDIR)main.o 

$(SUBDIR)part1.o: part1.cpp part1.h
	$(CC) -c part1.cpp -o $(SUBDIR)part1.o 

$(SUBDIR)part2.o: part2.cpp part2.h
	$(CC) -c part2.cpp -o $(SUBDIR)part2.o 

dir:
	mkdir -p $(SUBDIR)

clean:
	rm -f $(OBJS)

run:
	./$(SUBDIR)$(EXE)

help:
	echo -e "Available targets: all, main.o, part1.o, part2.o, clean, help."
