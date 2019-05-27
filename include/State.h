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

 public:
  State(sf::RenderWindow* window);
  virtual ~State();

  /* end state function */
  virtual void endState() = 0;

  /* pure virtual */
  /* make sure when inheritence, inherited class must implement pure virtual function */
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

#endif
