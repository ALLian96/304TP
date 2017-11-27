
CC=gcc -Wall

terrains:generation_terrains.o test_generation_terrains.o terrains.o robot.o
	$(CC) terrains -o generation_terrains.o test_generation_terrains.o robot.o
terrains.o:terrains.c terrains.h robot.c robot.h
	$(CC) -c terrains.c robot.c
generation_terrains.o:generation_terrains.c generation_terrains.h
	$(CC) -c generation_terrains.c
test_generation_terrains.o: generation_terrains.h generation_terrains.c test_generation_terrains.c
	$(CC) -c test_generation_terrains.c generation_terrains.c
clean:
	rm -f $(terrains) *.o
	
	
	
	
	
	
	
	
	
	
CC=gcc -Wall

PROGRAMMES=test_terrain test_robot robot_terrain curiosity curiosity-test

all: $(PROGRAMMES)

######################################################################
#                       Règles de compilation                        #
######################################################################

%.o: %.c
	$(CC) -c $<

test_terrain.o: test_terrain.c terrain.h

test_robot.o: test_robot.c robot.h

robot_terrain.o: robot_terrain.c terrain.h robot.h

robot.o: robot.c robot.h

terrain.o: terrain.c terrain.h

environnement.o: environnement.c environnement.h robot.h terrain.h

programme.o: programme.c programme.h type_pile.h

interprete.o: interprete.c interprete.h environnement.h \
	programme.h type_pile.h robot.h terrain.h

interprete%.o: interprete%.c interprete.h environnement.h \
	programme.h type_pile.h robot.h terrain.h

type_pile.o: type_pile.c type_pile.h

curiosity.o: curiosity.c environnement.h programme.h \
	interprete.h robot.h terrain.h type_pile.h

curiosity-test.o: curiosity-test.c environnement.h programme.h \
	interprete.h robot.h terrain.h type_pile.h

######################################################################
#                       Règles d'édition de liens                    #
######################################################################

test_terrain: test_terrain.o terrain.o
	$(CC) $^ -o $@

test_robot: test_robot.o robot.o
	$(CC) $^ -o $@

robot_terrain: robot_terrain.o terrain.o robot.o
	$(CC) $^ -o $@

curiosity: curiosity.o environnement.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test: curiosity-test.o environnement.o programme.o interprete.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

curiosity-test%: curiosity-test.o environnement.o programme.o interprete%.o \
	robot.o terrain.o type_pile.o
	$(CC) $^ -o $@

clean:
	rm -f $(PROGRAMMES) *.o
