LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

game:
	g++ -c Game.cpp -o game.o

main:
	g++ -c main.cpp -o main.o

all: main game
	@echo "** Building the Game**"
	g++ -o main game.o main.o $(LIBS)

clean:
	@echo "** Removing object files and excutables**"
	rm -f main *.o
