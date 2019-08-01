#ifndef __TILE_H__
#define __TILE_H__

enum TileTypes {DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER, LIMIT};

class Tile {
private:

protected:
  sf::Sprite shape;
  bool collision;
  short type;

public:
  Tile();
  Tile(int x, int y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rect,  bool collision = false, short type = TileTypes::DEFAULT);
  virtual ~Tile();

  // accessors

  const short& getType() const;
  const bool getCollision() const;
  const sf::Vector2f& getPosition() const;
  const sf::FloatRect getGlobalBounds() const;
  const bool intersects(const sf::FloatRect& bounds) const;
  const std::string getAsString() const;

  // functions
  virtual void update();
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f());

};


#endif
