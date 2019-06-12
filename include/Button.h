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

  sf::Color textIdleColor;
  sf::Color textHoverColor;
  sf::Color textActiveColor;

  sf::Color idleColor;
  sf::Color hoverColor;
  sf::Color activeColor;


public:
  Button(float x, float y, float width, float height, sf::Font* font, std::string text, unsigned character_size, sf::Color text_idle_color,  sf::Color text_hover_color,  sf::Color text_active_color, sf::Color idle_color, sf::Color hover_color, sf::Color active_color );
  virtual ~Button();


  // accessors
  const bool isPressed() const;
  // functions
  void render(sf::RenderTarget* target);
  void update(const sf::Vector2f& mousePos);
};

#endif
