#
# Filename: Makefile
# Contains: Makefile for lab session about Heaps for COMP15
# Part of: Lab assignment "Heaps" for Comp 15 Fall 2018
#
 
CC = clang++
CFLAGS = -Wall -Wextra -c -std=c++11
DEPS = Heap.h MinHeap.h Patient.h Queue.h

%.o: %.cpp $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

er: er.o Heap.o Patient.o MinHeap.o Queue.o
	$(CC) -o er er.o Heap.o Patient.o MinHeap.o Queue.o


clean:
	rm -f *.o core* *~ er
