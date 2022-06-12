#
# Makefile for SixDegrees
#
# Project1 (fall 2018)
# originally from hw4
# modified by Mengqi Irina Wang
#

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

SixDegrees: main.o SixDegrees.o Actor.o Stack.o Queue.o LinkedList.o Graph.o
	${CXX} ${LDFLAGS} -o $@ $^

graphtest: LDLIBS   += -lpthread -lgtest
graphtest: Graph.o runalltests.o \
           test-graph.o SixDegrees.o Actor.o Stack.o Queue.o LinkedList.o 
	${CXX}  -o $@ $^ ${LDFLAGS} ${LDLIBS}

clean:
	rm -rf SixDegrees *.o *.dSYM

provide:
	provide comp15 hw5 main.cpp SixDegrees.cpp SixDegrees.h test-graph.cpp \
			runalltests.cpp README Makefile Queue.cpp Queue.h Actor.cpp \
			Actor.h LinkedList.cpp LinkedList.h Graph.cpp Graph.h Stack.cpp \
			Stack.h NodeType.h
