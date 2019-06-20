#ifndef __GAME_H__
#define __GAME_H__

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
