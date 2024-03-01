# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -O3
INCLUDES = -Iinclude

# Target executable name
TARGET = out

# Find source files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:src/%.cpp=%.o) main.o

# Default rule to build the program
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# Rule for object files
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp

# Clean rule
clean:
	rm -f $(OBJS) $(TARGET)
