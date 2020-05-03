#ifndef __CHARACTER_TAB_H__
#define __CHARACTER_TAB_H__
#include "Tab.h"

class CharacterTab : public Tab{
private:
  sf::RectangleShape back;
  sf::Text infoText;

public:
  CharacterTab(sf::VideoMode& vm, sf::Font& font, Player& player);
  virtual ~CharacterTab();

  void update();
  void render(sf::RenderTarget* target) ;
};

#endif
