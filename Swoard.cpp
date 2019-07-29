#include "include/stdafx.h"
#include "include/Swoard.h"

Swoard::Swoard() {

  // Visual Weapon
  if(!this->weapon_texture.loadFromFile("Resource/images/sprites/player/sword.png")) {
    std::cout << "ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE" << std::endl;
  }

  this->weapon_sprite.setTexture(this->weapon_texture);

  this->weapon_sprite.setOrigin(this->weapon_sprite.getGlobalBounds().width / 2.f,
                                this->weapon_sprite.getGlobalBounds().height
                                );
}


Swoard::~Swoard() {}

void Swoard::update(const sf::Vector2f& mouse_pos_view, const sf::Vector2f center) {
  // update visual weapon
  this->weapon_sprite.setPosition(center);

  float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
  float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

  const float PI = 3.14159265;
  float deg = atan2(dY, dX) * 180 / PI;

  this->weapon_sprite.setRotation(deg + 90.f);

}

void Swoard::render(sf::RenderTarget& target, sf::Shader* shader)  {
  if(shader) {
    target.draw(this->weapon_sprite, shader);
  } else {
    target.draw(this->weapon_sprite);
  }
}
