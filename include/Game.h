#ifndef __GAME_H__
#define __GAME_H__

#include "State.h"
#include "GraphicsSettings.h"

class Game {
 private:
  // Variables
  GraphicsSettings gfxSettings;
  StateData stateData;
  sf::RenderWindow* window;
  sf::Event sfEvent;

  // Delta time
  sf::Clock dtClock;
  float dt;

  std::stack<State*> states;

  std::map<std::string, int> supportedKeys;
  float gridSize;

  // Initialization
  void initVariables();
  void initWindow();
  void initStateData();
  void initStates();
  void initKeys();
  void initGraphicsSettings();

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
