#include "include/stdafx.h"
#include "include/RegularTile.h"

RegularTile::RegularTile(short type, int x, int y, float gridSizeF,
                         const sf::Texture& texture, const sf::IntRect& rect,
                         bool collision)
  : Tile(type, x, y, gridSizeF, texture, rect, collision) {
}

RegularTile::~RegularTile() {}

// Functions

const std::string RegularTile::getAsString() const {
  std::stringstream ss;

  ss << this->type << " "
     << this->shape.getTextureRect().left << " "
     << this->shape.getTextureRect().top << " "
     << this->collision;

  return ss.str();
}



void RegularTile::update() {
}

void RegularTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition) {
  if(shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", playerPosition);

    target.draw(this->shape, shader);
  } else {
    target.draw(this->shape);
  }
}
