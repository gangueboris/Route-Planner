CXX = g++
CXXFLAGS = -Wall -Wextra 

SRC = main.cpp Graph.cpp
HEADERS = Graph.hpp Route.hpp Waypoint.hpp
OBJ = $(SRC:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
