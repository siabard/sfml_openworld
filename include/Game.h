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

class Game {
 private:
  // Variables
  sf::RenderWindow* window;
  sf::Event sfEvent;

  // Initialization
  void initWindow();

 public:

  // Constructor
  Game();

  // Destructor
  virtual ~Game();

  // Functions
  void updateSFMLEvents();
  void update();
  void render();
  void run();
};

#endif
