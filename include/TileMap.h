#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include "Entity.h"
#include "Tile.h"

class TileMap {
private:
  float gridSizeF;
  int gridSizeI;
  sf::Vector2i maxSizeWorldGrid;
  sf::Vector2f maxSizeWorld;
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
  virtual ~TileMap();


  // accessors
  const sf::Texture* getTileSheet() const;
  const int getLayerSize(const int x, const int y, const int layer) const;

  // functions
  void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type);
  void removeTile(const int x, const int y, const int z);

  void loadFromFile(const std::string file_name);
  void saveToFile(const std::string file_name);

  void updateCollision(Entity* entity, const float& dt);

  void update();
  void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader = nullptr, const  sf::Vector2f playerPosition = sf::Vector2f(), const bool show_collision = false);
  void renderDeferred(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());
};

#endif
