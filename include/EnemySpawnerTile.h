#ifndef __ENEMYSPAWNER_H__
#define __ENEMYSPAWNER_H__

#include "Tile.h"

class EnemySpawnerTile
  : public Tile {
private:

  int enemyType;
  int enemyAmount;
  sf::Int32 enemyTimeToSpawn;
  float enemyMaxDistance;
  bool spawned;
  sf::Clock enemySpawnTimer;

public:
  EnemySpawnerTile(int x, int y, float gridSizeF,
               const sf::Texture& texture, const sf::IntRect& rect,
               int enemyType,
                   int enemyAmount, sf::Int32 enemyTimeToSpawn, float enemyMaxDistance);
  virtual ~EnemySpawnerTile();
  virtual const std::string getAsString() const;

  // accessors
  void setSpawned(const bool spawned);
  bool getSpawned() const;
  const bool canSpawn() const;

  // functions
  void update();
  void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());

};

#endif
