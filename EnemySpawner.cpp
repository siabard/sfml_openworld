#include "include/stdafx.h"
#include "include/EnemySpawner.h"

EnemySpawner::EnemySpawner(int x, int y, float gridSizeF,
                           const sf::Texture& texture, const sf::IntRect& rect,
                           int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance)
  : Tile(TileTypes::ENEMYSPAWNER, x, y, gridSizeF, texture, rect, false), enemyType(enemyType), enemyAmount(enemyAmount), enemyTimeToSpawn(enemyTimeToSpawn), enemyMaxDistance(enemyMaxDistance) {


}

EnemySpawner::~EnemySpawner() {}

// functions

const std::string EnemySpawner::getAsString() const {
  std::stringstream ss;

  /**
     x, y, z (done in tilemap save)
     type,
     rect x, rect y,
     enmy type,
     enmy amount,
     enmy tts,
     enmy distance,
   */
  ss << this->type << " "
     << this->shape.getTextureRect().left << " "
     << this->shape.getTextureRect().top << " "
     << this->enemyType << " "
     << this->enemyAmount << " "
     << this->enemyTimeToSpawn << " "
     << this->enemyMaxDistance
    ;

  return ss.str();
}

void EnemySpawner::update() {

}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition) {
  if(shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", playerPosition);

    target.draw(this->shape, shader);
  } else {
    target.draw(this->shape);
  }
}
