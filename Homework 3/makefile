CXX = g++
CXXFLAGS = -Wall -std=c++11

TARGET = store_app

SRCS = main.cpp store.cpp product.cpp transaction.cpp person.cpp address.cpp credit_card.cpp
OBJS = $(SRCS:.cpp=.o)

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)