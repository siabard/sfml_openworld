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

  // functions
  const std::string getAsString() const;

  void update();
  void render(sf::RenderTarget& target);

};


#endif
