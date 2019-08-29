#include "include/stdafx.h"
#include "include/EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int x, int y, float gridSizeF,
                           const sf::Texture& texture, const sf::IntRect& rect,
                           int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance)
  : Tile(TileTypes::ENEMYSPAWNER, x, y, gridSizeF, texture, rect, false), enemyType(enemyType), enemyAmount(enemyAmount), enemyTimeToSpawn(enemyTimeToSpawn), enemyMaxDistance(enemyMaxDistance), spawned(false) {


}

EnemySpawnerTile::~EnemySpawnerTile() {}

// functions

const std::string EnemySpawnerTile::getAsString() const {
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

void EnemySpawnerTile::setSpawned(const bool spawned) {
  this->spawned = spawned;
}

bool EnemySpawnerTile::getSpawned() const {
  return this->spawned;
}

void EnemySpawnerTile::update() {

}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPosition) {
  if(shader) {
    shader->setUniform("hasTexture", true);
    shader->setUniform("lightPos", playerPosition);

    target.draw(this->shape, shader);
  } else {
    target.draw(this->shape);
  }
}
