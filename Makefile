CXX = g++
CXXFLAGS = -Wall

q: main.o
	$(CXX) $(CXXFLAGS) -o q main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean :
	-rm *.o q
