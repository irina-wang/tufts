#
#  Makefile
#  COMP15
#  Spring 2019
#


CC = clang++
CFLAGS = -std=c++11 -Wall -Wextra -g3
DEPS = MetroSim.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MetroSim: main.o MetroSim.o
	$(CC) -o MetroSim main.o MetroSim.o

unittest: LDLIBS += -lgtest -lpthread
unittest: MetroSim.o unittest.o
	$(CC) -o ${LDFLAGS} $@ $^ ${LDLIBS}

clean:
	rm -f *.o core* *~ MetroSim
