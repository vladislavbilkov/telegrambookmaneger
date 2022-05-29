CXXFLAGS = -Wall -g

LIBS = --std=c++14 -I/usr/local/include -lTgBot -lboost_system -lssl -lcrypto -lpthread

compile: 
	mkdir -p bin
	g++ $(CXXFLAGS) src/main.cpp -o bin/telegram_bot src/BotLogics.cpp $(LIBS)

clean:
	rm -rf src/*.o bin/
