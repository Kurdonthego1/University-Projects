CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = assign3zox610

all: $(TARGET)

$(TARGET): main.o sorts.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o sorts.o

main.o: main.cpp sorts.h
	$(CXX) $(CXXFLAGS) -c main.cpp

sorts.o: sorts.cpp sorts.h
	$(CXX) $(CXXFLAGS) -c sorts.cpp

clean:
	rm -f *.o $(TARGET)