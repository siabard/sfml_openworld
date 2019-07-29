#ifndef __SWOARD_H__
#define __SWOARD_H__

#include "MeleeWeapon.h"

class Swoard : public MeleeWeapon {

private:

public:

  Swoard();
  virtual ~Swoard();

  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) ;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) ;
};

#endif
