#include "include/stdafx.h"
#include "include/EnemySpawner.h"

EnemySpawner::EnemySpawner(int x, int y, float gridSizeF,
                           const sf::Texture& texture, const sf::IntRect& rect,
                           float grid_size, int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance)
  : Tile(x, y, gridSizeF, texture, rect, false, TileTypes::ENEMYSPAWNER), enemyType(enemyType), enemyAmount(enemyAmount), enemyTimeToSpawn(enemyTimeToSpawn), enemyMaxDistance(enemyMaxDistance) {


}

EnemySpawner::~EnemySpawner() {}

// functions
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
