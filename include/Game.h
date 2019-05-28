#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "State.h"

class Game {
 private:
  // Variables
  sf::RenderWindow* window;
  sf::Event sfEvent;

  // Delta time
  sf::Clock dtClock;
  float dt;

  std::stack<State*> states;

  // Initialization
  void initWindow();
  void initStates();

 public:

  // Constructor
  Game();

  // Destructor
  virtual ~Game();

  // Functions

  // Regular
  void endApplication();

  // updates
  void updateDt();
  void updateSFMLEvents();
  void update();

  // render
  void render();

  // core
  void run();
};

#endif
