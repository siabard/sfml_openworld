#ifndef __SWORD_H__
#define __SWORD_H__

#include "MeleeWeapon.h"

class Sword : public MeleeWeapon {

private:

public:

  Sword(unsigned value, std::string texture_file);
  virtual ~Sword();

  virtual Sword* clone();

  virtual void update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center);
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) ;
};

#endif
