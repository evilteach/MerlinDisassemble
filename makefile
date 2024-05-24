#
CXX = g++

CXXFLAGS = -Wall -g -std=c++11

TARGET = MerlinDisassemble

SRC = MerlinDisassemble.cpp
HDR = MerlinDisassemble.hpp

$(TARGET): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm $(TARGET)
