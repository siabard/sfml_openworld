#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

#include "State.h"

class Game {
 private:
  // Variables
  sf::RenderWindow* window;
  sf::Event sfEvent;
  std::vector<sf::VideoMode> videoModes;
  sf::ContextSettings windowSettings;
  bool fullscreen;
  // Delta time
  sf::Clock dtClock;
  float dt;

  std::stack<State*> states;

  std::map<std::string, int> supportedKeys;

  // Initialization
  void initVariables();
  void initWindow();
  void initStates();
  void initKeys();

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
