#ifndef __RAT_H__
#define __RAT_H__

#include "Enemy.h"

class Rat
: public Enemy {
private:
  // variables
public:
  Rat(float x, float y, sf::Texture& texture);
  virtual ~Rat();

  // initilizer
  void initVariables();
  void initAnimation();

  // functions
  void updateAnimation(const float& dt);
  void update(const float& dt, sf::Vector2f& mouse_pos_view);
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false);
};

#endif
