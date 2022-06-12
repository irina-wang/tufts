#
# Makefile for hookbook
# Big Three Lab
# Comp 15 Fall 2018
#
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra
LDFLAGS  = -g3

HDRS = HookBookBattles.h Abilities.h
SRCS = main.cpp HookBookBattles.cpp Abilities.cpp
OBJS = main.o   HookBookBattles.o   Abilities.o

hookbookBattles:  ${OBJS} ${HDRS}
	${CXX} ${LDFLAGS} -o hookbookBattles ${OBJS}

valgrind:  hookbookBattles
	valgrind ./hookbookBattles

clean:
	rm -rf hookbookBattles ${OBJS} *~ *.dSYM

provide:
	provide comp15 lab7 main.cpp HookBookBattles.cpp HookBookBattles.h \
		Abilities.h Abilities.cpp Makefile README

main.o:              main.cpp HookBookBattles.h Abilities.h
HookBookBattles.o:   HookBookBattles.cpp HookBookBattles.h Abilities.h
Abilities.o:         Abilities.cpp Abilities.h
