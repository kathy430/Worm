all: game
CPP=g++
CFLAGS=-std=c++11

game: main.o gameview.o screen.o worm.o
	$(CPP) -ggdb -o game main.o gameview.o screen.o worm.o -lcurses -ltermcap

main.o: main.cpp gameview.hpp screen.hpp worm.hpp
	$(CPP) -c main.cpp $(CFLAGS)

gameview.o: gameview.cpp screen.hpp worm.hpp
	$(CPP) -c -ggdb gameview.cpp -lcurses -ltermcap

screen.o: screen.cpp worm.hpp
	$(CPP) -c screen.cpp $(CFLAGS)

worm.o: worm.cpp worm.hpp
	$(CPP) -c worm.cpp $(CFLAGS)

clean:
	rm -f *.o *~