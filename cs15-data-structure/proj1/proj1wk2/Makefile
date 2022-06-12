#
# Makefile for SequenceMatch
#
# Project1 (fall 2018)
# originally from hw4
# modified by Mengqi Irina Wang
#
# Not using -Wextra

CXX      = clang++
CXXFLAGS = -std=c++11 -g3 -Wall -Wextra
LDFLAGS  = -g3

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

SeqMatch: main.o SequenceMatch.o 
	${CXX} ${LDFLAGS} -o SeqMatch main.o SequenceMatch.o 

unittests: LDLIBS   += -lpthread -lgtest
unittests: SequenceMatch.o runalltests.o \
           SequenceMatch-unittest.o 
	${CXX}  -o $@ $^ ${LDFLAGS} ${LDLIBS}

clean:
	rm -rf SeqMatch *.o *.dSYM

provide:
	provide comp15 proj1wk2 main.cpp SequenceMatch.cpp SequenceMatch.h \
	         SequenceMatch-unittest.cpp runalltests.cpp README Makefile

