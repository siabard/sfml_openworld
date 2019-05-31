#ifndef __STATE_HPP_
#define __STATE_HPP_

#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include "Entity.h"

class State{
private:

 protected:
  sf::RenderTarget* window;
  std::map<std::string, int>* supportedKeys;
  std::map<std::string, int> keybinds;

  bool quit;

  std::vector<sf::Texture> textures;

  // FUNCTIONS
  virtual void initKeybinds() = 0;

 public:
  State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys );
  virtual ~State();

  const bool& getQuit() const;
  virtual void checkForQuit();
  virtual void endState() = 0;

  /* pure virtual */
  /* make sure when inheritence, inherited class must implement pure virtual function */
  /* end state function */
  virtual void updateInput(const float& dt) = 0;
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
