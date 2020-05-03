#ifndef __TAB_H__
#define __TAB_H__

#include "Player.h"
#include "Gui.h"

class Tab {
 protected:
  sf::Font& font;
  sf::VideoMode& vm;
  Player& player;

 public:
  Tab(sf::VideoMode& vm, sf::Font& font,  Player& player);
  virtual ~Tab();

  virtual void update() = 0;
  virtual void render(sf::RenderTarget* target) = 0;
};
#endif
