#############################################################################
#
#    Tufts University, Comp 160 randSelect coding assignment  
#    Makefile
#
#############################################################################


CXX      = g++
CXXFLAGS = -std=c++11 -g -O2 -Wall -Wextra

randSelect: main.o randSelect.o
	$(CXX) $(CXXFLAGS) -o randSelect main.o randSelect.o

main.o: main.cpp randSelect.h
	$(CXX) $(CXXFLAGS) -c main.cpp

randSelect.o: randSelect.cpp randSelect.h
	$(CXX) $(CXXFLAGS) -c randSelect.cpp

clean:
	rm -f randSelect *.o *~