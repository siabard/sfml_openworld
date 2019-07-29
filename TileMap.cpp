#include "include/stdafx.h"
#include "include/TileMap.h"

void TileMap::clear() {

  if(!this->map.empty()) {

    for(int x = 0; x < this->maxSizeWorldGrid.x; x++) {
      for(int y = 0; y < this->maxSizeWorldGrid.y; y++) {
        for(int z = 0; z < this->layers; z++) {

          for(size_t k = 0; k < this->map[x][y][z].size(); k++) {

            if(this->map[x][y][z][k] != nullptr)
              delete this->map[x][y][z][k];

            this->map[x][y][z][k] = nullptr;
          }
          this->map[x][y][z].clear();
        }

        this->map[x][y].clear();
      }

      this->map[x].clear();
    }

    this->map.clear();
  }

  //std::cout << this->map.size() << std::endl;
}

TileMap::TileMap(const float gridSize, int width, int height, std::string texture_file) : gridSizeF(gridSize), textureFile(texture_file) {
  this->gridSizeI = static_cast<int>(gridSize);
  this->maxSizeWorldGrid.x = width;
  this->maxSizeWorldGrid.y = height;

  this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
  this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;

  this->layers = 1;

  this->fromX = 0;
  this->toX = 0;
  this->fromY = 0;
  this->toY = 0;
  this->layer = 0;

  this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());
  for(int x = 0; x < this->maxSizeWorldGrid.x; x++) {

    for(int y = 0; y < this->maxSizeWorldGrid.y; y++) {

      this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

      for(int z = 0; z < this->layers; z++) {

        this->map[x][y].resize(this->layers, std::vector< Tile* >() );
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

TileMap::TileMap(const std::string file_name) {

  this->fromX = 0;
  this->toX = 0;
  this->fromY = 0;
  this->toY = 0;
  this->layer = 0;

  this->loadFromFile(file_name);

  this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
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

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition, sf::Shader* shader, const sf::Vector2f playerPosition, const bool show_collision) {

    this->layer = 0;

    this->fromX = gridPosition.x - 15;
    if(this->fromX < 0)
      this->fromX = 0;
    else if(this->fromX >= this->maxSizeWorldGrid.x)
      this->fromX = this->maxSizeWorldGrid.x;

    this->toX = gridPosition.x + 16;
    if(this->toX < 0)
      this->toX = 0;
    else if(this->toX > this->maxSizeWorldGrid.x)
      this->toX = this->maxSizeWorldGrid.x;

    this->fromY = gridPosition.y - 8;
    if(this->fromY < 0)
      this->fromY = 0;
    else if(this->fromY > this->maxSizeWorldGrid.y)
      this->fromY = this->maxSizeWorldGrid.y;

    this->toY = gridPosition.y + 9;
    if(this->toY < 0)
      this->toY = 0;
    else if(this->toY > this->maxSizeWorldGrid.y)
      this->toY = this->maxSizeWorldGrid.y;


    for(int x = this->fromX; x < this->toX; x++) {
      for(int y = this->fromY; y < this->toY; y++) {

        if(!this->map[x][y][this->layer].empty()) {
          for(size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {

            if(this->map[x][y][this->layer][k]->getType() == TileTypes::DOODAD) {
              this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
            } else {
              if(shader) {
                this->map[x][y][this->layer][k]->render(target, shader, playerPosition);
              } else {
                this->map[x][y][this->layer][k]->render(target);
              }
            }

            if (show_collision) {
              if(this->map[x][y][this->layer][k]->getCollision()) {
                this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
                target.draw(this->collisionBox);
              }
            }
          }
        }
      }
    }

}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader,const sf::Vector2f playerPosition) {
  while(!this->deferredRenderStack.empty()) {
    if(shader) {
      this->deferredRenderStack.top()->render(target, shader, playerPosition);
    } else {
      this->deferredRenderStack.top()->render(target);
    }
    this->deferredRenderStack.pop();
  }
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool collision, const short type) {
  /* Take three indices from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it */

  if( x < this->maxSizeWorldGrid.x &&
      x >= 0 &&
      y < this->maxSizeWorldGrid.y &&
      y >= 0 &&
      z < this->layers &&
      z >= 0
      ) {
    this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type));
  }

}

void TileMap::removeTile(const int x, const int y, const int z) {
  /* Take three indices from the mouse position in the grid and remove a tile at that position if the internal tilemap array allows it */
  if( x < this->maxSizeWorldGrid.x &&
      x >= 0 &&
      y < this->maxSizeWorldGrid.y &&
      y >= 0 &&
      z < this->layers &&
      z >= 0
      ) {
    if (!this->map[x][y][z].empty()) {
      delete this->map[x][y][z][ this->map[x][y][z].size()-1 ];
      this->map[x][y][z].pop_back();
    }
  }
}

void TileMap::loadFromFile(const std::string file_name) {

  std::ifstream in_file;

  in_file.open(file_name);
  if(in_file.is_open()) {
    sf::Vector2i size;
    int gridSizeI = 0;
    int layers = 0;
    std::string texture_file = "";

    int x = 0;
    int y = 0;
    int z = 0;
    int tr_x = 0;
    int tr_y = 0;
    bool collision = false;
    short type = TileTypes::DEFAULT;


    // basic
    in_file >> size.x >> size.y >> gridSizeI >> layers >> texture_file;

    // tiles
    this->gridSizeF = static_cast<float>(gridSizeI);
    this->gridSizeI = gridSizeI;
    this->maxSizeWorldGrid.x = size.x;
    this->maxSizeWorldGrid.y = size.y;
    this->maxSizeWorldF.x = static_cast<float>(size.x) * this->gridSizeF;
    this->maxSizeWorldF.y = static_cast<float>(size.y) * this->gridSizeF;
    this->layers = layers;
    this->textureFile = texture_file;

    this->clear();

    this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector< std::vector<Tile*> > >());

    for(int x = 0; x < this->maxSizeWorldGrid.x; x++) {

      for(int y = 0; y < this->maxSizeWorldGrid.y; y++) {

        this->map[x].resize(this->maxSizeWorldGrid.y, std::vector< std::vector<Tile*> >());

        for(int z = 0; z < this->layers; z++) {
          this->map[x][y].resize(this->layers, std::vector<Tile*>());

        }
      }
    }

    if(!this->tileSheet.loadFromFile(texture_file)) {
      std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << texture_file << std::endl;
    }

    // Load all Tiles
    while(in_file >> x >> y >> z >> tr_x >> tr_y >> collision >> type) {
      this->map[x][y][z].push_back( new Tile(x, y,
                                             gridSizeF,
                                             this->tileSheet,
                                             sf::IntRect(tr_x, tr_y, static_cast<int>(gridSizeI), static_cast<int>(gridSizeI)),
                                             collision, type
                                             )
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
             << this->gridSizeI << std::endl
             << this->layers << std::endl
             << this->textureFile << std::endl
      ;

    for(int x = 0; x < this->maxSizeWorldGrid.x; x++) {
      for(int y = 0; y < this->maxSizeWorldGrid.y; y++) {
        for(int z = 0; z < this->layers; z++) {
          if(!this->map[x][y][z].empty())
            for(size_t k = 0; k < this->map[x][y][z].size(); k++) {
              out_file << x << " "
                       << y << " "
                       << z << " "
                       << this->map[x][y][z][k]->getAsString()
                       << " "; // make sure this last space is not saved.
            }
        }
      }
    }

  } else {
    std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;
  }

  out_file.close();
}

// accessors

const bool TileMap::tileEmpty(const int x, const int y, const int z) const {
  if(x >= 0 && x < this->maxSizeWorldGrid.x &&
     y >= 0 && y < this->maxSizeWorldGrid.y &&
     z >= 0 && z < this->layers ) {
    return this->map[x][y][z].empty();
  }

  return false;
}

const sf::Texture* TileMap::getTileSheet() const {
  return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const {
  if(x >= 0 && x < static_cast<int>(this->map.size())) {
    if(y >= 0 && y < static_cast<int>(this->map[x].size())) {
      if(layer >= 0 && layer < static_cast<int>(this->map[x][y].size())) {
        return static_cast<int>(this->map[x][y][layer].size());
      }
    }
  }

  return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const {
  return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeF() const {
  return this->maxSizeWorldF;
}

void TileMap::updateCollision(Entity* entity, const float& dt) {

  // WORLD BOUNDS
  if(entity->getPosition().x < 0.f) {
    entity->setPosition(0.f, entity->getPosition().y);
    entity->stopVelocityX();
  } else if(entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {
    entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width ,
                        entity->getPosition().y);
    entity->stopVelocityX();
  }

  if(entity->getPosition().y < 0.f) {
    entity->setPosition(entity->getPosition().x, 0.f);
    entity->stopVelocityY();
  } else if(entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {
    entity->setPosition(entity->getPosition().x,
                        this->maxSizeWorldF.y - entity->getGlobalBounds().height
                        );
    entity->stopVelocityY();
  }

  // TILES : check around player

  this->layer = 0;

  this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
  if(this->fromX < 0)
    this->fromX = 0;
  else if(this->fromX > this->maxSizeWorldGrid.x)
    this->fromX = this->maxSizeWorldGrid.x;

  this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
  if(this->toX < 0)
    this->toX = 0;
  else if(this->toX > this->maxSizeWorldGrid.x)
    this->toX = this->maxSizeWorldGrid.x;

  this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
  if(this->fromY < 0)
    this->fromY = 0;
  else if(this->fromY > this->maxSizeWorldGrid.y)
    this->fromY = this->maxSizeWorldGrid.y;

  this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
  if(this->toY < 0)
    this->toY = 0;
  else if(this->toY > this->maxSizeWorldGrid.y)
    this->toY = this->maxSizeWorldGrid.y;

  for(int x = this->fromX; x < this->toX; x++) {
    for(int y = this->fromY; y < this->toY; y++) {
      if(!this->map[x][y][this->layer].empty()) {
        for(size_t k = 0; k < this->map[x][y][this->layer].size(); k++) {

          sf::FloatRect playerBounds = entity->getGlobalBounds();
          sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
          sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

          if (this->map[x][y][this->layer][k]->getCollision() &&
              this->map[x][y][this->layer][k]->intersects(nextPositionBounds)) {
            // Bottom Collision
            if (playerBounds.top < wallBounds.top
                && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left
                ) {
              entity->stopVelocityY();
              entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
            } else if (playerBounds.top > wallBounds.top

                       && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                       && playerBounds.left < wallBounds.left + wallBounds.width
                       && playerBounds.left + playerBounds.width > wallBounds.left
                       ) {
              // Top collision
              entity->stopVelocityY();
              entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
            } else if (playerBounds.left < wallBounds.left
                       && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                       && playerBounds.top < wallBounds.top + wallBounds.height
                       && playerBounds.top + playerBounds.height > wallBounds.top
                       ) {
              // Right Collision
              entity->stopVelocityX();
              entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
            } else if (playerBounds.left > wallBounds.left
                       && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                       && playerBounds.top < wallBounds.top + wallBounds.height
                       && playerBounds.top + playerBounds.height > wallBounds.top
                       ) {
              // Left Collision
              entity->stopVelocityX();
              entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
            }
          }
        }
      }
    }
  }
}
