#
#  Makefile
#  COMP15
#  Spring 2019
#
#  Makefile for the train-conductor.cpp, LinkedList and Station
#


CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -g3 
INCLUDES = LinkedList.h

%.o: %.cpp $(INCLUDES)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

unittests: LDLIBS   += -lgtest -lpthread
unittests:  runalltests.o LinkedList-unittest.o LinkedList.o
	$(CXX) -o ${LDFLAGS} $@ $^ ${LDLIBS}

clean:
	rm -f *.o core* *~ unittests
