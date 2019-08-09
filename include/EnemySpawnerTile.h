#ifndef __ENEMYSPAWNER_H__
#define __ENEMYSPAWNER_H__

#include "Tile.h"

class EnemySpawnerTile
  : public Tile {
private:

  int enemyType;
  int enemyAmount;
  int enemyTimeToSpawn;
  float enemyMaxDistance;

public:
  EnemySpawnerTile(int x, int y, float gridSizeF,
               const sf::Texture& texture, const sf::IntRect& rect,
               int enemyType,
               int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance);
  virtual ~EnemySpawnerTile();
  virtual const std::string getAsString() const;

  // functions
  void update();
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());

};

#endif
