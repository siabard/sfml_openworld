#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "Tile.h"

class TileMap {
private:
  float gridSizeF;
  unsigned gridSizeU;
  sf::Vector2u maxSize;
  unsigned layers;
  std::vector< std::vector< std::vector<Tile > > > map;

public:
  TileMap();
  virtual ~TileMap();

  // fucntions
  void update();
  void render(sf::RenderTarget& target);
};

#endif
