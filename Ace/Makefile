CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = plane_war
OBJS = main.o Game.o Entity.o Utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) save.txt