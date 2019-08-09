#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "Entity.h"
#include "Tile.h"
#include "RegularTile.h"
#include "EnemySpawnerTile.h"

class Tile;
class RegularTile;
class Entity;
class EnemySpawner;

class TileMap {
private:
  float gridSizeF;
  int gridSizeI;
  sf::Vector2i maxSizeWorldGrid;
  sf::Vector2f maxSizeWorldF;
  int layers;
  std::vector< std::vector< std::vector< std::vector<Tile*> > > > map;
  std::stack<Tile*> deferredRenderStack;
  sf::Texture tileSheet;
  std::string textureFile;
  sf::RectangleShape collisionBox;

  void clear();

  // Culling
  int fromX;
  int toX;
  int fromY;
  int toY;
  int layer;

public:
  TileMap(const float gridSize, int width, int height, std::string texture_file);
  TileMap(const std::string file_name);
  virtual ~TileMap();


  // accessors
  const bool tileEmpty(const int x, const int y, const int z) const;
  const sf::Texture* getTileSheet() const;
  const int getLayerSize(const int x, const int y, const int layer) const;
  const sf::Vector2i& getMaxSizeGrid() const;
  const sf::Vector2f& getMaxSizeF() const;

  // functions
  void addTile(const short type, const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision);
  void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const int enemy_type, const int enemy_amount, const int enemy_tts, const int enemy_md);
  void removeTile(const int x, const int y, const int z, const int type = -1);

  void loadFromFile(const std::string file_name);
  void saveToFile(const std::string file_name);
  const bool checkType(const int x, const int y, const int z, const short type) const;

  void update(Entity* entity, const float& dt);

  void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader = nullptr, const  sf::Vector2f playerPosition = sf::Vector2f(), const bool show_collision = false);
  void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
};

#endif
