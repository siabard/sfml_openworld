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

  // accessors
  const sf::Vector2f& getPosition() const;
  const sf::FloatRect getGlobalBounds() const;

  // modifiers
  void setPosition(const sf::Vector2f& position);
  void setPosition(const float x, const float y);

  // functions

  bool intersects(const sf::FloatRect& frect);
  void update();
  void render(sf::RenderTarget& target);

};

#endif
