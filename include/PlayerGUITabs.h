#ifndef __PLAYER_GUI_TABS_H__
#define __PLAYER_GUI_TABS_H__

#include "CharacterTab.h"

class PlayerGUITabs {

private:
  sf::Font& font;
  sf::VideoMode& vm;
  Player& player;

  // Character Tab
  CharacterTab characterTab;

public:
  PlayerGUITabs(sf::VideoMode& vm, sf::Font& font, Player& player);
  virtual ~PlayerGUITabs();

  void update();
  void render(sf::RenderTarget* target);
};

#endif
