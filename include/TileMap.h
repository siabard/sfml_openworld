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
  std::string textureFile;
  void clear();

public:
  TileMap(const float gridSize, unsigned width, unsigned height, std::string texture_file);
  virtual ~TileMap();


  // accessors
  const sf::Texture* getTileSheet() const;

  // functions
  void update();
  void render(sf::RenderTarget& target);

  void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect);
  void removeTile(const unsigned x, const unsigned y, const unsigned z);

  void loadFromFile(const std::string file_name);
  void saveToFile(const std::string file_name);
};

#endif
