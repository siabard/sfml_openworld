#include "include/stdafx.h"
#include "include/EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
                         std::map<std::string, sf::Texture>& textures)
  : activeEnemies(activeEnemies), textures(textures) {}

EnemySystem::~EnemySystem() {}


void EnemySystem::createEnemy(short type, const float xPos, const float yPos) {
  switch(type) {
  case EnemyTypes::RAT:
    this->activeEnemies.push_back(new Rat(xPos, yPos, this->textures["RAT1_SHEET"]));
    break;

  defaut:
    std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << std::endl;
    break;
  }
}

void EnemySystem::update(const float dt) {

}

void EnemySystem::render(sf::RenderTarget* target) {}
