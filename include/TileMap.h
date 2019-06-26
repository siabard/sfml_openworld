#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "Tile.h"

class TileMap {
private:
  float gridSizeF;
  unsigned gridSizeU;
  sf::Vector2u maxSize;
  unsigned layers;
  std::vector< std::vector< std::vector<Tile* > > > map;
  sf::Texture tileSheet;


public:
  TileMap(const float gridSize, unsigned width, unsigned height);
  virtual ~TileMap();


  // accessors
  const sf::Texture* getTileSheet() const;

  // fucntions
  void update();
  void render(sf::RenderTarget& target);

  void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
  void removeTile(const unsigned x, const unsigned y, const unsigned z);
};

#endif
