CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = atm
SRCS = main.cpp ATM.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = ATM.h User.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
