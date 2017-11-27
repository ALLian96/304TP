CC=gcc -Wall

all: test_generation_terrains

robot.o:robot.c robot.h
	$(CC) -c robot.c

terrain.o:terrain.c terrain.h robot.h
	$(CC) -c terrain.c 

generation_terrains.o:generation_terrains.c generation_terrains.h terrain.h
	$(CC) -c generation_terrains.c

test_generation_terrains.o: generation_terrains.h generation_terrains.c terrain.h test_generation_terrains.c
	$(CC) -c test_generation_terrains.c generation_terrains.c


test_generation_terrains: robot.o terrain.o generation_terrains.o test_generation_terrains.o
	$(CC) robot.o terrain.o generation_terrains.o test_generation_terrains.o -o test_generation_terrains
clean:
	rm -f test_generation_terrains*.o
	
	
	
