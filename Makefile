LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

entity:
	g++ -g -c Entity.cpp -o entity.o

game:
	g++ -g -c Game.cpp -o game.o

gamestate:
	g++ -g -c States/GameState.cpp -o gamestate.o

mainmenustate:
	g++ -g -c States/MainMenuState.cpp -o mainmenustate.o

main:
	g++ -g -c main.cpp -o main.o

state:
	g++ -g -c State.cpp -o state.o

button:
	g++ -g -c Resource/Button.cpp -o button.o

player:
	g++ -g -c Player.cpp -o player.o

all: main game state gamestate entity mainmenustate button player
	@echo "** Building the Game**"
	g++ -o main entity.o mainmenustate.o gamestate.o state.o game.o button.o player.o main.o $(LIBS)

clean:
	@echo "** Removing object files and excutables**"
	rm -f main *.o
