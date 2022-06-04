CXX = g++
CXXFLAGS = -Wall -g

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

LIBS = --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread

src/%.o: src/%.cpp
	$(CXX) -c $< $(CXXFLAGS) -o $@

compile: $(OBJ)
	mkdir -p bin
	$(CXX) $(LIBS) $(CXXFLAGS) $^ -o bin/bots

clean:
	rm -rf src/*.o bin/
