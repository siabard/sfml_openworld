#ifndef __PAUSE_MENU_H__
#define __PAUSE_MENU_H__

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <map>
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
  PauseMenu(sf::RenderWindow& window, sf::Font& font);
  virtual ~PauseMenu();

  // accessors
  std::map<std::string, gui::Button*>& getButtons();

  // Functions
  const bool isButtonPressed(const std::string key);
  void addButton(const std::string key, float y, const std::string text);
  void update(const sf::Vector2f& mousePos);
  void render(sf::RenderTarget& target);
};


#endif
