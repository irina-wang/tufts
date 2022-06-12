#
# Filename: Graph.cpp
# Contains: Makefile for lab session about graphs 
# Part of: Lab assignment "Graph Traversal" for Comp 15
#
CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11
DEPS = Graph.h Queue.h Stack.h
 
 %.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

search: search-campus.o Graph.o Queue.o Stack.o
	$(CC) -o search search-campus.o Graph.o Queue.o Stack.o

clean:
	rm -f *.o core* *~ search
