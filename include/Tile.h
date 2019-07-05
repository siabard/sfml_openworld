#ifndef __TILE_H__
#define __TILE_H__

enum TileTypes {DEFAULT = 0, DAMAGING, LIMIT};

class Tile {
private:

protected:
  sf::RectangleShape shape;
  bool collision;
  short type;

public:
  Tile();
  Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& rect,  bool collision = false, short type = TileTypes::DEFAULT);
  virtual ~Tile();

  // accessors
  const bool getCollision() const;
  const sf::Vector2f& getPosition() const;
  const sf::FloatRect getGlobalBounds() const;
  const bool intersects(const sf::FloatRect& bounds) const;
  const std::string getAsString() const;
  // functions
  void update();
  void render(sf::RenderTarget& target);

};


#endif
