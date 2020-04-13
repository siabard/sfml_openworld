#include "include/stdafx.h"
#include "include/EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
                         std::map<std::string, sf::Texture>& textures)
  : activeEnemies(activeEnemies), textures(textures) {}

EnemySystem::~EnemySystem() {}


void EnemySystem::createEnemy(short type, const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile) {
  switch(type) {
  case EnemyTypes::RAT:
    enemy_spawner_tile.increaseEnemyCounter();
    this->activeEnemies.push_back(new Rat(xPos, yPos, this->textures["RAT1_SHEET"], enemy_spawner_tile));
    break;

  default:
    std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << std::endl;
    break;
  }
}


void EnemySystem::removeEnemy(const int index) {
  this->activeEnemies[index]->getEnemySpanwerTile().decreaseEnemyCounter();

  delete this->activeEnemies[index];
  this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float dt) {

}

void EnemySystem::render(sf::RenderTarget* target) {}
