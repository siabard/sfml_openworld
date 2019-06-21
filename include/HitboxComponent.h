#ifndef __HITBOX_COMPONENT_H__
#define __HITBOX_COMPONENT_H__

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