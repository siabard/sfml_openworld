PROJ_NAME=main
CC=g++
CCFLAGS=-Wall -g -c
LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
SOURCES=$(wildcard *.cpp */*.cpp)
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))

all: $(PROJ_NAME)
	@echo Running application
	@echo
	@./$(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@echo linking...
	$(CC) -o $@ $^ $(LIBS)

%.o: %.cpp %.h
	@echo Compiling and generating object $@ ...
	$(CC) $< $(CCFLAGS) -o $@

clean:
	@echo Remove
	@rm -rf objects $(OBJ) $(PROJ_NAME)
	@echo done!
