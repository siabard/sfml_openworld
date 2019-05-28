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

class State{
 private:
  sf::RenderTarget* window;
  std::vector<sf::Texture> textures;
  bool quit;

 public:
  State(sf::RenderWindow* window);
  virtual ~State();

  const bool& getQuit() const;
  virtual void checkForQuit();
  virtual void endState() = 0;

  /* pure virtual */
  /* make sure when inheritence, inherited class must implement pure virtual function */
  /* end state function */
  virtual void updateKeybinds(const float& dt) = 0;
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
