#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "Entity.h"
#include "Tile.h"

class TileMap {
private:
  float gridSizeF;
  unsigned gridSizeU;
  sf::Vector2u maxSizeWorldGrid;
  sf::Vector2f maxSizeWorld;
  unsigned layers;
  std::vector< std::vector< std::vector<Tile* > > > map;
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
  TileMap(const float gridSize, unsigned width, unsigned height, std::string texture_file);
  virtual ~TileMap();


  // accessors
  const sf::Texture* getTileSheet() const;

  // functions
  void update();
  void render(sf::RenderTarget& target, Entity* entity = nullptr);

  void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type);
  void removeTile(const unsigned x, const unsigned y, const unsigned z);

  void loadFromFile(const std::string file_name);
  void saveToFile(const std::string file_name);

  void updateCollision(Entity* entity, const float& dt);
};

#endif
