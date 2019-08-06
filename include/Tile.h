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
  Tile(short type, int x, int y, float gridSizeF,
       const sf::Texture& texture, const sf::IntRect& rect, const bool collision);
  virtual ~Tile();

  // accessors

  const short& getType() const;
  virtual const bool getCollision() const;
  virtual const sf::Vector2f& getPosition() const;
  virtual const sf::FloatRect getGlobalBounds() const;
  virtual const bool intersects(const sf::FloatRect& bounds) const;
  virtual const std::string getAsString() const = 0;

  // functions
  virtual void update() = 0;
  virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const sf::Vector2f playerPosition = sf::Vector2f()) = 0;

};


#endif
