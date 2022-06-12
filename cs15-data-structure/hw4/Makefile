#
# Makefile for Binary Search Tree
#
# Homework 4 (fall 2018)
# combined by Mengqi Irina Wang
#
# Not using -Wextra

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

hw4: main.o BinarySearchTree.o pretty_print.o
	${CXX} ${LDFLAGS} -o hw4 main.o BinarySearchTree.o pretty_print.o

unittests: LDLIBS   += -lpthread -lgtest
unittests: BinarySearchTree.o runalltests.o pretty_print.o \
           BinarySearchTree-unittest.o 
	${CXX}  -o $@ $^ ${LDFLAGS} ${LDLIBS}

clean:
	rm -rf hw4 *.o *.dSYM

provide:
	provide comp15 hw4 main.cpp BinarySearchTree.cpp BinarySearchTree.h \
	        pretty_print.cpp README Makefile

