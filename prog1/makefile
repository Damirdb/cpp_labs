CXX = g++
CXXFLAGS = -Wall -std=c++17
SRC = main.cpp Club.cpp Time.cpp KaraokeClub.cpp DanceClub.cpp VIPKaraokeClub.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
