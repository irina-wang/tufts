 #
 # Filename: Makefile
 # Contains: Makefile for lab session about AVL Trees for COMP15
 # Part of: Lab assignment "AVL Trees" for Comp 15
 #
 

CXX      = clang++
CXXFLAGS = -std=c++11 -g -Wall -Wextra
LDFLAGS  = -g

lab: main.o AVLTree.o pretty_print.o
	${CXX} ${LDFLAGS} -o lab main.o AVLTree.o pretty_print.o

main.o:              main.cpp AVLTree.h 
AVLTree.o:  AVLTree.cpp AVLTree.h
pretty_print.o:      pretty_print.cpp AVLTree.h

clean:
	rm -rf lab *.o *.dSYM

provide:
	provide comp15 lab10 main.cpp AVLTree.cpp AVLTree.h \
	        pretty_print.cpp README Makefile

