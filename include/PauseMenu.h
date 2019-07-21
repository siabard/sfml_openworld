#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include "Gui.h"

class PauseMenu {
private:
  sf::Font& font;
  sf::Text menuText;

  sf::RectangleShape background;
  sf::RectangleShape container;


  std::map<std::string, gui::Button*> buttons;

  // private functions


public:
  PauseMenu(const sf::VideoMode& vm, sf::Font& font);
  virtual ~PauseMenu();

  // accessors
  std::map<std::string, gui::Button*>& getButtons();

  // Functions
  const bool isButtonPressed(const std::string key);
  void addButton(const std::string key, const float y, const float width, const float height, const unsigned charSize, const std::string text);
  void update(const sf::Vector2i& mousePos);
  void render(sf::RenderTarget& target);
};


#endif
