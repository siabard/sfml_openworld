#ifndef __ENEMYSYSTEM_H__
#define __ENEMYSYSTEM_H__

#include "stdafx.h"
#include "EnemySpawnerTile.h"
#include "Rat.h"

enum EnemyTypes {RAT = 0};

class EnemySystem {
private:
  std::vector<Enemy*>& activeEnemies;
  std::map<std::string, sf::Texture>& textures;

public:
  EnemySystem(std::vector<Enemy*>& activeEnemies,
              std::map<std::string, sf::Texture>& textures);
  virtual ~EnemySystem();

  // accessors

  // modifiers

  // function
  void createEnemy(short type, const float xPos, const float yPos);

  void update(const float dt);
  void render(sf::RenderTarget* target);
};

#endif
