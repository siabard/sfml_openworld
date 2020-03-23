#include "include/stdafx.h"
#include "include/Bow.h"

Bow::Bow(unsigned level, unsigned value, std::string texture_file) : RangedWeapon(level, value, texture_file) {}

Bow::~Bow() {

}

Bow* Bow::clone() {
  return new Bow(*this);
}

void Bow::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) {
  // update visual weapon
  this->weapon_sprite.setPosition(center);

  float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
  float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

  const float PI = 3.14159265f;
  float deg = atan2(dY, dX) * 180.f / PI;

  this->weapon_sprite.setRotation(deg + 90.f);
}
void Bow::render(sf::RenderTarget& target, sf::Shader* shader) {
  if(shader) {
    target.draw(this->weapon_sprite, shader);
  } else {
    target.draw(this->weapon_sprite);
  }
}
