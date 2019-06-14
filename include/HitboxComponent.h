#ifndef __HITBOX_COMPONENT_H__
#define __HITBOX_COMPONENT_H__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

class HitboxComponent {

private:
  sf::Sprite& sprite;
  sf::RectangleShape hitbox;
  float offsetX;
  float offsetY;

public:
  HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
  virtual ~HitboxComponent();

  // functions

  bool checkIntersect(const sf::FloatRect& frect);
  void update();
  void render(sf::RenderTarget& target);

};

#endif
