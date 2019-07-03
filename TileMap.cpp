#include "include/stdafx.h"
#include "include/TileMap.h"

void TileMap::clear() {
  for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {
    for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {
      for(size_t z = 0; z < this->layers; z++) {
        if(this->map[x][y][z] != nullptr)
          delete this->map[x][y][z];

        this->map[x][y][z] = nullptr;
      }

      this->map[x][y].clear();
    }

    this->map[x].clear();
  }

  this->map.clear();

  std::cout << this->map.size() << std::endl;
}

TileMap::TileMap(const float gridSize, unsigned width, unsigned height, std::string texture_file) : gridSizeF(gridSize), textureFile(texture_file) {
  this->gridSizeU = static_cast<unsigned>(gridSize);
  this->maxSizeWorldGrid.x = width;
  this->maxSizeWorldGrid.y = height;

  this->maxSizeWorld.x = static_cast<float>(width) * gridSize;
  this->maxSizeWorld.y = static_cast<float>(height) * gridSize;

  this->layers = 1;

  this->fromX = 0;
  this->toX = 0;
  this->fromY = 0;
  this->toY = 0;
  this->layer = 0;

  this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile* > >());
  for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {

    for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {

      this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

      for(size_t z = 0; z < this->layers; z++) {

        this->map[x][y].resize(this->layers, nullptr);
      }
    }
  }

  if(!this->tileSheet.loadFromFile(texture_file)) {
    std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << std::endl;
  }

  this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
  this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
  this->collisionBox.setOutlineColor(sf::Color::Red);
  this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap() {
  this->clear();
}

// Functions
void TileMap::update() {

}

void TileMap::render(sf::RenderTarget& target, Entity* entity) {
  if(entity) {
    this->layer = 0;

    this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
    if(this->fromX < 0)
      this->fromX = 0;
    else if(this->fromX >= this->maxSizeWorldGrid.x)
      this->fromX = this->maxSizeWorldGrid.x;

    this->toX = entity->getGridPosition(this->gridSizeU).x + 3;
    if(this->toX < 0)
      this->toX = 0;
    else if(this->toX > this->maxSizeWorldGrid.x)
      this->toX = this->maxSizeWorldGrid.x;

    this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
    if(this->fromY < 0)
      this->fromY = 0;
    else if(this->fromY > this->maxSizeWorldGrid.y)
      this->fromY = this->maxSizeWorldGrid.y;

    this->toY = entity->getGridPosition(this->gridSizeU).y + 3;
    if(this->toY < 0)
      this->toY = 0;
    else if(this->toY > this->maxSizeWorldGrid.y)
      this->toY = this->maxSizeWorldGrid.y;


    for(size_t x = this->fromX; x < this->toX; x++) {
      for(size_t y = this->fromY; y < this->toY; y++) {

        if( this->map[x][y][this->layer] != nullptr) {
          this->map[x][y][this->layer]->render(target);
          if(this->map[x][y][this->layer]->getCollision()) {
            this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
            target.draw(this->collisionBox);
          }
        }
      }
    }
  } else {

    for(auto &x : this->map) {
      for(auto &y : x) {
        for(auto &z : y) {
          if(z != nullptr) {
            z->render(target);
            if(z->getCollision()) {
              this->collisionBox.setPosition(z->getPosition());
              target.draw(this->collisionBox);
            }
          }
        }
      }
    }
  }

}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool collision, const short type) {
  /* Take three indices from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it */

  if( x < this->maxSizeWorldGrid.x &&
      x >= 0 &&
      y < this->maxSizeWorldGrid.y &&
      y >= 0 &&
      z < this->layers &&
      z >= 0
      ) {
    if (this->map[x][y][z] == nullptr) { // OK to add
      this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
    }
  }

}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
  /* Take three indices from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it */
  if( x < this->maxSizeWorldGrid.x &&
      x >= 0 &&
      y < this->maxSizeWorldGrid.y &&
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

void TileMap::loadFromFile(const std::string file_name) {

  std::ifstream in_file;

  in_file.open(file_name);
  if(in_file.is_open()) {
    sf::Vector2u size;
    unsigned gridSizeU = 0;
    unsigned layers = 0;
    std::string texture_file = "";

    unsigned x = 0;
    unsigned y = 0;
    unsigned z = 0;
    unsigned tr_x = 0;
    unsigned tr_y = 0;
    bool collision = false;
    short type = TileTypes::DEFAULT;


    // basic
    in_file >> size.x >> size.y >> gridSizeU >> layers >> texture_file;

    // tiles
    this->gridSizeF = static_cast<float>(gridSizeU);
    this->gridSizeU = gridSizeU;
    this->maxSizeWorldGrid.x = size.x;
    this->maxSizeWorldGrid.y = size.y;
    this->layers = layers;
    this->textureFile = texture_file;


    if(!this->tileSheet.loadFromFile(texture_file)) {
      std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << std::endl;
    }

    this->clear();
    this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile* > >());

    for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {

      for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {

        this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

        for(size_t z = 0; z < this->layers; z++) {

          this->map[x][y].resize(this->layers, nullptr);
        }
      }
    }

    // Load all Tiles
    while(in_file >> x >> y >> z >> tr_x >> tr_y >> collision >> type) {
      this->map[x][y][z] = new Tile(x, y,
                                    gridSizeF,
                                    this->tileSheet,
                                    sf::IntRect(tr_x, tr_y, static_cast<int>(gridSizeU), static_cast<int>(gridSizeU)),
                                    collision, type
                                    );
    }

  } else {
    std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;
  }

  in_file.close();
}


void TileMap::saveToFile(const std::string file_name) {
  // What kind of structure do we have?
  // Saves the entire timemap to a text-file
  /** format:
      Basic:
      Size x y
      gridSize
      layers
      texture file

      All tiles:
      x y z gridPos x y (Texture rect x y w h), collision type

   */

  std::ofstream out_file;

  out_file.open(file_name);
  if(out_file.is_open()) {
    out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << std::endl
             << this->gridSizeU << std::endl
             << this->layers << std::endl
             << this->textureFile << std::endl
      ;

    for(size_t x = 0; x < this->maxSizeWorldGrid.x; x++) {
      for(size_t y = 0; y < this->maxSizeWorldGrid.y; y++) {
        for(size_t z = 0; z < this->layers; z++) {
          if(this->map[x][y][z] != nullptr)
            out_file << x << " "
                     << y << " "
                     << z << " "
                     << this->map[x][y][z]->getAsString()
                     << " "; // make sure this last space is not saved.
        }
      }
    }

  } else {
    std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;
  }

  out_file.close();
}

// accessors
const sf::Texture* TileMap::getTileSheet() const {
  return &this->tileSheet;
}

void TileMap::updateCollision(Entity* entity) {

  // WORLD BOUNDS
  if(entity->getPosition().x < 0.f) {
    entity->setPosition(0.f, entity->getPosition().y);
    entity->stopVelocityX();
  } else if(entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorld.x) {
    entity->setPosition(this->maxSizeWorld.x - entity->getGlobalBounds().width ,
                        entity->getPosition().y);
    entity->stopVelocityX();
  }

  if(entity->getPosition().y < 0.f) {
    entity->setPosition(entity->getPosition().x, 0.f);
    entity->stopVelocityY();
  } else if(entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y) {
    entity->setPosition(entity->getPosition().x,
                        this->maxSizeWorld.y - entity->getGlobalBounds().height
                        );
    entity->stopVelocityY();
  }

  // TILES : check around player

  this->layer = 0;

  this->fromX = entity->getGridPosition(this->gridSizeU).x - 1;
  if(this->fromX < 0)
    this->fromX = 0;
  else if(this->fromX > this->maxSizeWorldGrid.x)
    this->fromX = this->maxSizeWorldGrid.x;

  this->toX = entity->getGridPosition(this->gridSizeU).x + 3;
  if(this->toX < 0)
    this->toX = 0;
  else if(this->toX > this->maxSizeWorldGrid.x)
    this->toX = this->maxSizeWorldGrid.x;

  this->fromY = entity->getGridPosition(this->gridSizeU).y - 1;
  if(this->fromY < 0)
    this->fromY = 0;
  else if(this->fromY > this->maxSizeWorldGrid.y)
    this->fromY = this->maxSizeWorldGrid.y;

  this->toY = entity->getGridPosition(this->gridSizeU).y + 3;
  if(this->toY < 0)
    this->toY = 0;
  else if(this->toY > this->maxSizeWorldGrid.y)
    this->toY = this->maxSizeWorldGrid.y;

  for(size_t x = this->fromX; x < this->toX; x++) {
    for(size_t y = this->fromY; y < this->toY; y++) {

      if(this->map[x][y][this->layer] != nullptr) {
        if (this->map[x][y][this->layer]->getCollision() &&
            this->map[x][y][this->layer]->intersects(entity->getGlobalBounds())) {
          std::cout << "COLLISION" << std::endl;
        }
      }
    }
  }
}
