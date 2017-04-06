OBJS = GraphType.o SolveA.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

main.o: main.cpp SolveA.h
	$(CC) $(CFLAGS) main.cpp

SolveA.o: SolveA.h SolveA.cpp GraphType.h 
	$(CC) $(CFLAGS) SolveA.cpp

GraphType.o: GraphType.h GraphType.cpp
	$(CC) $(CFLAGS) GraphType.cpp

clean:
	\rm *.o p1
