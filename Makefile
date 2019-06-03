LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

entity:
	g++ -c Entity.cpp -o entity.o

game:
	g++ -c Game.cpp -o game.o

gamestate:
	g++ -c States/GameState.cpp -o gamestate.o

mainmenustate:
	g++ -c States/MainMenuState.cpp -o mainmenustate.o

main:
	g++ -c main.cpp -o main.o

state:
	g++ -c State.cpp -o state.o

all: main game state gamestate entity mainmenustate
	@echo "** Building the Game**"
	g++ -o main entity.o mainmenustate.o gamestate.o state.o game.o main.o $(LIBS)

clean:
	@echo "** Removing object files and excutables**"
	rm -f main *.o
