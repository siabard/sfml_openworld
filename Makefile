CCFLAGS=-Wall -g -c
LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

entity:
	g++ $(CCFLAGS) Entity.cpp -o entity.o

game:
	g++ $(CCFLAGS) Game.cpp -o game.o

gamestate:
	g++ $(CCFLAGS) States/GameState.cpp -o gamestate.o

mainmenustate:
	g++ $(CCFLAGS) States/MainMenuState.cpp -o mainmenustate.o

main:
	g++ $(CCFLAGS) main.cpp -o main.o

state:
	g++ $(CCFLAGS) State.cpp -o state.o

button:
	g++ $(CCFLAGS) Resource/Button.cpp -o button.o

player:
	g++ $(CCFLAGS) Player.cpp -o player.o

movementcomponent:
	g++ $(CCFLAGS) MovementComponent.cpp -o movementcomponent.o

all: main game state gamestate entity mainmenustate button player movementcomponent
	@echo "** Building the Game**"
	g++ -o main entity.o mainmenustate.o gamestate.o state.o game.o button.o player.o movementcomponent.o main.o $(LIBS)



clean:
	@echo "** Removing object files and excutables**"
	rm -f main *.o
