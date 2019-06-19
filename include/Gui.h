#ifndef __GUI_H__
#define __GUI_H__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>

enum button_states {BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui {
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
    const std::string& getText() const;

    // functions
    void setText(const std::string text);
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2f& mousePos);
  };

  class DropDownList {
  private:
    float keytime;
    float keytimeMax;

    sf::Font& font;
    gui::Button* activeElement;
    std::vector<gui::Button*> list;
    bool showList;

  public:

    DropDownList(float x, float y,  float width, float height,  sf::Font& font, std::string list[], unsigned numOfElements, unsigned default_index);
    virtual ~DropDownList();

    // functions
    const bool getKeytime();
    void updateKeytime(const float& dt);
    void render(sf::RenderTarget& target);
    void update(const sf::Vector2f& mousePos, const float& dt);

  };
}
#endif
