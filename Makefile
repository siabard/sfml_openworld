LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

game:
	g++ -c Game.cpp -o game.o

gamestate:
	g++ -c States/GameState.cpp -o gamestate.o

main:
	g++ -c main.cpp -o main.o

state:
	g++ -c State.cpp -o state.o

all: main game state gamestate
	@echo "** Building the Game**"
	g++ -o main gamestate.o state.o game.o main.o $(LIBS)

clean:
	@echo "** Removing object files and excutables**"
	rm -f main *.o
