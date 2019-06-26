#include "include/stdafx.h"
#include "include/TileMap.h"

TileMap::TileMap(const float gridSize, unsigned width, unsigned height) : gridSizeF(gridSize) {
  this->gridSizeU = static_cast<unsigned>(gridSize);
  this->maxSize.x = width;
  this->maxSize.y = height;
  this->layers = 1;

  this->map.resize(this->maxSize.x, std::vector< std::vector<Tile* > >());
  for(size_t x = 0; x < this->maxSize.x; x++) {

    for(size_t y = 0; y < this->maxSize.y; y++) {

      this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

      for(size_t z = 0; z < this->layers; z++) {

        this->map[x][y].resize(this->layers, nullptr);
      }
    }
  }

  if(!this->tileSheet.loadFromFile("Resource/images/tiles/tilesheet1.png")) {
    std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET." << std::endl;
  }
}

TileMap::~TileMap() {
  for(size_t x = 0; x < this->maxSize.x; x++) {
    for(size_t y = 0; y < this->maxSize.y; y++) {
      for(size_t z = 0; z < this->layers; z++) {
        if(this->map[x][y][z] != nullptr)
          delete this->map[x][y][z];
      }
    }
  }
}

// Functions
void TileMap::update() {

}

void TileMap::render(sf::RenderTarget& target) {
  for(auto &x : this->map) {
    for(auto &y : x) {
      for(auto &z : y) {
        if(z != nullptr)
          z->render(target);
      }
    }
  }
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect) {
  /* Take three indices from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it */

  if( x < this->maxSize.x &&
      x >= 0 &&
      y < this->maxSize.y &&
      y >= 0 &&
      z < this->layers &&
      z >= 0
      ) {
    if (this->map[x][y][z] == nullptr) { // OK to add
      this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texture_rect);
    }
  }

}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
  /* Take three indices from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it */
  if( x < this->maxSize.x &&
      x >= 0 &&
      y < this->maxSize.y &&
      y >= 0 &&
      z < this->layers &&
      z >= 0
      ) {
    if (this->map[x][y][z] != nullptr) { // OK to add
      delete this->map[x][y][z];
      this->map[x][y][z] = nullptr;
    }
  }

}


// accessors
const sf::Texture* TileMap::getTileSheet() const {
  return &this->tileSheet;
}
