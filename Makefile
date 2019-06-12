PROJ_NAME=main
CC=g++
CCFLAGS=-Wall -g -c -fstack-protector
LIBS=-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system
SOURCES :=  $(wildcard **/*.cpp) $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SOURCES))

all: $(PROJ_NAME)
	@echo Running application
	@echo
	@./$(PROJ_NAME)

$(PROJ_NAME): $(OBJS)
	@echo linking...
	$(CC) -o $@ $^ $(LIBS)

%.o: %.cpp
	@echo Compiling and generating object $@ ...
	$(CC) $< $(CCFLAGS) -o $@

clean:
	@echo Remove
	@rm -rf $(OBJS) $(PROJ_NAME)
	@echo done!
