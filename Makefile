OBJS = GraphType.o ShortestPath.o SolveA.o SolveB.o SolveC.o GreedySolveA.o GreedySolveB.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

p1 : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o p1

main.o: main.cpp SolveA.h SolveB.h SolveC.h GreedySolveA.h
	$(CC) $(CFLAGS) main.cpp

SolveA.o: SolveA.h SolveA.cpp GraphType.h ShortestPath.h
	$(CC) $(CFLAGS) SolveA.cpp

SolveB.o: SolveB.h SolveB.cpp GraphType.h ShortestPath.h
	$(CC) $(CFLAGS) SolveB.cpp

SolveC.o: SolveC.h SolveC.cpp GraphType.h ShortestPath.h
	$(CC) $(CFLAGS) SolveC.cpp

GreedySolveA.o: GreedySolveA.h GreedySolveA.cpp GraphType.h ShortestPath.h
	$(CC) $(CFLAGS) GreedySolveA.cpp

GreedySolveB.o: GreedySolveB.h GreedySolveB.cpp GraphType.h ShortestPath.h
	$(CC) $(CFLAGS) GreedySolveB.cpp

ShortestPath.o: ShortestPath.h ShortestPath.cpp GraphType.h
	$(CC) $(CFLAGS) ShortestPath.cpp

GraphType.o: GraphType.h GraphType.cpp
	$(CC) $(CFLAGS) GraphType.cpp

clean:
	\rm *.o p1
