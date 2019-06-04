#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>


enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};
class Button {
private:

  short unsigned buttonState;

  sf::RectangleShape shape;
  sf::Font* font;
  sf::Text text;

  sf::Color idleColor;
  sf::Color hoverColor;
  sf::Color activeColor;

public:
  Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor );
  virtual ~Button();


  // accessors
  const bool isPressed() const;
  // functions
  void render(sf::RenderTarget* target);
  void update(const sf::Vector2f& mousePos);
};

#endif
