#ifndef __ENEMYSPAWNER_H__
#define __ENEMYSPAWNER_H__

#include "Tile.h"

class EnemySpawner
  : public Tile {
private:

  int enemyType;
  int enemyAmount;
  int enemyTimeToSpawn;
  float enemyMaxDistance;

public:
  EnemySpawner(int x, int y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rect,  float grid_size, int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance);
  virtual ~EnemySpawner();

  // functions
  void update();
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());

};

#endif
